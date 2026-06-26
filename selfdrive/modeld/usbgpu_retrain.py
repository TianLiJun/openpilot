#!/usr/bin/env python3
import ctypes
import os
import subprocess
import time
from dataclasses import dataclass
from pathlib import Path

from openpilot.selfdrive.modeld.helpers import USBGPU_PID, USBGPU_VID

USB_CTRL_PATH = Path("/sys/devices/platform/soc/a600000.ssusb")
PORTLI_PATH = USB_CTRL_PATH / "portli"
PORTSC_PATH = USB_CTRL_PATH / "portsc"
POWER_PATHS = (
  Path("/sys/bus/usb/devices/4-1/power/control"),
  Path("/sys/bus/usb/devices/usb4/power/control"),
  USB_CTRL_PATH / "power/control",
)
DEFAULT_LOG_PATH = Path("/data/tmp/usb_retrain_search_v2.tsv")
DEFAULT_SNAPSHOT_PATH = Path("/data/tmp/usb_golden_snapshot.txt")
USBGPU_PATH = Path("/sys/bus/usb/devices/4-1")
HARD_DMESG_PATTERNS = (
  "error -71",
  "device descriptor",
  "not accepting address",
  "Cannot set link state",
  "disconnect",
)


@dataclass(frozen=True)
class LinkSample:
  start: int
  end: int
  delta: int
  seconds: float
  err_per_s: float
  hard_errors: int
  resets: int
  dmesg_known: bool


@dataclass(frozen=True)
class RetrainResult:
  passed: bool
  attempts: int
  time_to_stable_s: float
  err_per_s: float | None = None


def _log(cloudlog, msg: str) -> None:
  if cloudlog is not None:
    cloudlog.warning(msg)
  else:
    print(msg, flush=True)


def _read_hex(path: Path) -> int:
  return int(path.read_text().strip(), 16)


def _run(cmd: list[str], timeout: float = 5.0) -> subprocess.CompletedProcess:
  return subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=timeout)


def _clear_dmesg() -> bool:
  for cmd in (["dmesg", "-C"], ["sudo", "-n", "dmesg", "-C"]):
    try:
      if _run(cmd).returncode == 0:
        return True
    except Exception:
      pass
  return False


def _read_dmesg() -> str:
  for cmd in (["dmesg"], ["sudo", "-n", "dmesg"]):
    try:
      r = _run(cmd)
      if r.returncode == 0:
        return r.stdout
    except Exception:
      pass
  return ""


def _count_dmesg(text: str) -> tuple[int, int]:
  hard = sum(text.count(p) for p in HARD_DMESG_PATTERNS)
  resets = text.count("reset SuperSpeed")
  return hard, resets


def _set_power_on() -> None:
  for path in POWER_PATHS:
    try:
      path.write_text("on")
    except Exception:
      pass


def _read_text(path: Path) -> str | None:
  try:
    return path.read_text().strip()
  except Exception:
    return None


def _superspeed_device_ready() -> bool:
  return (
    _read_text(USBGPU_PATH / "idVendor") == "add1" and
    _read_text(USBGPU_PATH / "idProduct") == "0001" and
    _read_text(USBGPU_PATH / "speed") == "5000" and
    _read_text(USBGPU_PATH / "bConfigurationValue") == "1"
  )


def _wait_for_quiet_superspeed(settle_seconds: float, timeout: float, threshold: float, cloudlog=None) -> RetrainResult | None:
  if settle_seconds <= 0 or timeout <= 0:
    return None

  start_time = time.monotonic()
  last_reason = "not checked"
  while time.monotonic() - start_time < timeout:
    if not _superspeed_device_ready():
      last_reason = "USB GPU not configured at SuperSpeed"
      time.sleep(1.0)
      continue

    try:
      sample = _measure(settle_seconds)
    except Exception as e:
      last_reason = f"sample failed: {e}"
      time.sleep(1.0)
      continue

    elapsed = time.monotonic() - start_time
    if _sample_ok(sample, threshold):
      _log(cloudlog, f"usbgpu quiet SuperSpeed settle passed: {sample.err_per_s:.2f} err/s over {settle_seconds:.1f}s elapsed={elapsed:.1f}s")
      return RetrainResult(True, 0, elapsed, sample.err_per_s)

    last_reason = f"{sample.err_per_s:.2f} err/s hard={sample.hard_errors} resets={sample.resets}"
    _log(cloudlog, f"usbgpu quiet SuperSpeed settle not ready: {last_reason}")
    time.sleep(1.0)

  _log(cloudlog, f"usbgpu quiet SuperSpeed settle failed after {timeout:.1f}s: {last_reason}")
  return RetrainResult(False, 0, timeout, None)


def _usb_vendor_pcie_power_cycle(off_delay: float, on_delay: float) -> None:
  from tinygrad.runtime.autogen import libusb
  from tinygrad.runtime.support.usb import USB3, checked

  USB3.list_devices.cache_clear()
  devs = USB3.list_devices(USBGPU_VID, USBGPU_PID)
  if not devs:
    raise RuntimeError("USB GPU add1:0001 not found")

  handle = ctypes.POINTER(libusb.struct_libusb_device_handle)()
  checked(libusb.libusb_open)(devs[0][0], ctypes.byref(handle))
  try:
    checked(libusb.libusb_control_transfer, "F3 PCIe power off failed")(handle, 0x40, 0xF3, 0, 0, None, 0, 1000)
    time.sleep(off_delay)
    checked(libusb.libusb_control_transfer, "F3 PCIe power on failed")(handle, 0x40, 0xF3, 1, 0, None, 0, 1000)
    time.sleep(on_delay)
    checked(libusb.libusb_reset_device, "USB device reset failed")(handle)
  finally:
    try:
      libusb.libusb_close(handle)
    except Exception:
      pass
    USB3.list_devices.cache_clear()


def _measure(seconds: float, clear_dmesg: bool = True) -> LinkSample:
  dmesg_known = _clear_dmesg() if clear_dmesg else False
  start = _read_hex(PORTLI_PATH)
  time.sleep(seconds)
  end = _read_hex(PORTLI_PATH)
  delta = end - start if end >= start else end
  dmesg = _read_dmesg() if dmesg_known else ""
  hard, resets = _count_dmesg(dmesg)
  return LinkSample(start, end, delta, seconds, delta / max(seconds, 0.001), hard, resets, dmesg_known)


def _sample_ok(sample: LinkSample, threshold: float) -> bool:
  dmesg_ok = True if not sample.dmesg_known else sample.hard_errors == 0 and sample.resets == 0
  return sample.err_per_s <= threshold and dmesg_ok


def _append_log(path: Path, attempt: int, stage: str, off_delay: float, on_delay: float, sample: LinkSample, elapsed: float) -> None:
  path.parent.mkdir(parents=True, exist_ok=True)
  if not path.exists():
    path.write_text("time\telapsed_s\tattempt\tstage\toff_delay\ton_delay\tstart\tend\tdelta\tseconds\terr_per_s\thard_errors\tresets\tdmesg_known\tportsc\n")
  with path.open("a") as f:
    f.write(
      f"{int(time.time())}\t{elapsed:.2f}\t{attempt}\t{stage}\t{off_delay:.3f}\t{on_delay:.3f}\t"
      f"0x{sample.start:08x}\t0x{sample.end:08x}\t{sample.delta}\t{sample.seconds:.1f}\t"
      f"{sample.err_per_s:.2f}\t{sample.hard_errors}\t{sample.resets}\t{int(sample.dmesg_known)}\t"
      f"{PORTSC_PATH.read_text().strip() if PORTSC_PATH.exists() else 'missing'}\n"
    )


def _snapshot(path: Path, sample: LinkSample, attempts: int, time_to_stable_s: float) -> None:
  path.parent.mkdir(parents=True, exist_ok=True)
  lines = [
    f"time={time.ctime()}",
    "method=asm2464 F3 PCIe off/on + libusb_reset_device",
    f"attempts={attempts}",
    f"time_to_stable_s={time_to_stable_s:.2f}",
    f"confirm_start=0x{sample.start:08x}",
    f"confirm_end=0x{sample.end:08x}",
    f"confirm_delta={sample.delta}",
    f"confirm_seconds={sample.seconds:.1f}",
    f"confirm_err_per_s={sample.err_per_s:.2f}",
    f"confirm_hard_errors={sample.hard_errors}",
    f"confirm_resets={sample.resets}",
  ]
  for name in ("portsc", "portli", "port_pmsc", "port_hlpmc", "speed", "mode", "usb_compliance_mode", "xhci_link_compliance"):
    p = USB_CTRL_PATH / name
    if p.exists():
      lines.append(f"{name}={p.read_text().strip()}")
  for p in POWER_PATHS:
    if p.exists():
      lines.append(f"{p}= {p.read_text().strip()}")
  try:
    lines.append("lsusb_t=" + _run(["lsusb", "-t"]).stdout.strip().replace("\n", " | "))
  except Exception:
    pass
  path.write_text("\n".join(lines) + "\n")


def calibrate_usb_gpu_link_result(attempts: int = 8, threshold: float = 10.0, quick_seconds: float = 15.0,
                                  confirm_seconds: float = 60.0, log_path: Path = DEFAULT_LOG_PATH,
                                  snapshot_path: Path = DEFAULT_SNAPSHOT_PATH, cloudlog=None) -> RetrainResult:
  if os.getenv("USBGPU_RETRAIN", "1") == "0":
    _log(cloudlog, "usbgpu retrain disabled by USBGPU_RETRAIN=0")
    return RetrainResult(True, 0, 0.0, None)

  delay_pairs = [(0.25, 2.0), (0.50, 2.0), (0.25, 3.0), (0.75, 2.0), (1.00, 3.0), (0.25, 5.0)]
  _set_power_on()
  start_time = time.monotonic()
  _log(cloudlog, f"usbgpu retrain start: attempts={attempts} threshold={threshold:.1f} err/s")

  settle = _wait_for_quiet_superspeed(
    settle_seconds=float(os.getenv("USBGPU_SETTLE_SECONDS", "8")),
    timeout=float(os.getenv("USBGPU_SETTLE_TIMEOUT", "30")),
    threshold=float(os.getenv("USBGPU_SETTLE_THRESHOLD", str(threshold))),
    cloudlog=cloudlog,
  )
  if settle is not None and (settle.passed or os.getenv("USBGPU_RETRAIN_AFTER_SETTLE_FAIL", "0") == "0"):
    return settle

  for attempt in range(1, attempts + 1):
    off_delay, on_delay = delay_pairs[(attempt - 1) % len(delay_pairs)]
    try:
      _set_power_on()
      _usb_vendor_pcie_power_cycle(off_delay, on_delay)
      _set_power_on()
      sample = _measure(quick_seconds)
      elapsed = time.monotonic() - start_time
      _append_log(log_path, attempt, "quick", off_delay, on_delay, sample, elapsed)
      _log(cloudlog, f"usbgpu retrain attempt {attempt}: quick {sample.err_per_s:.2f} err/s elapsed={elapsed:.1f}s portli=0x{sample.end:08x}")
      if not _sample_ok(sample, threshold):
        continue
      if confirm_seconds <= 0:
        _snapshot(snapshot_path, sample, attempt, elapsed)
        _log(cloudlog, f"usbgpu retrain passed quick gate in {elapsed:.1f}s after {attempt} attempt(s); snapshot={snapshot_path}")
        return RetrainResult(True, attempt, elapsed, sample.err_per_s)

      confirm = _measure(confirm_seconds)
      elapsed = time.monotonic() - start_time
      _append_log(log_path, attempt, "confirm", off_delay, on_delay, confirm, elapsed)
      _log(cloudlog, f"usbgpu retrain attempt {attempt}: confirm {confirm.err_per_s:.2f} err/s elapsed={elapsed:.1f}s portli=0x{confirm.end:08x}")
      if _sample_ok(confirm, threshold):
        _snapshot(snapshot_path, confirm, attempt, elapsed)
        _log(cloudlog, f"usbgpu retrain passed in {elapsed:.1f}s after {attempt} attempt(s); snapshot={snapshot_path}")
        return RetrainResult(True, attempt, elapsed, confirm.err_per_s)
    except Exception as e:
      _log(cloudlog, f"usbgpu retrain attempt {attempt} failed: {e}")
      time.sleep(1.0)

  elapsed = time.monotonic() - start_time
  _log(cloudlog, f"usbgpu retrain failed to find a low-error link after {elapsed:.1f}s")
  return RetrainResult(False, attempts, elapsed, None)


def calibrate_usb_gpu_link(*args, **kwargs) -> bool:
  return calibrate_usb_gpu_link_result(*args, **kwargs).passed
