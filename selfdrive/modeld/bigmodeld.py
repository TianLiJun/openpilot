#!/usr/bin/env python3
import os

os.environ.setdefault("DEV", "USB+AMD:LLVM")
os.environ.setdefault("WARP_DEV", "QCOM")
os.environ.setdefault("FLOAT16", "1")
os.environ.setdefault("JIT_BATCH_SIZE", "0")
os.environ.setdefault("GMMU", "0")
os.environ.setdefault("HCQ_NUM_SDMA", "1")
os.environ.setdefault("XDG_CACHE_HOME", "/data/.cache")
os.environ.setdefault("CACHEDB", "/data/.cache/tinygrad/cache.db")
os.environ.setdefault("TMPDIR", "/data/tmp")
os.environ.setdefault("USBGPU_RETRAIN", "0")

import time
from openpilot.common.swaglog import cloudlog
from openpilot.common.params import Params
from openpilot.selfdrive.modeld.helpers import usbgpu_present, modeld_pkl_path
from openpilot.common.file_chunker import get_manifest_path
from openpilot.selfdrive.modeld.model_channel import BIG_CHANNEL
from openpilot.selfdrive.modeld.usbgpu_retrain import calibrate_usb_gpu_link_result


def main(demo=False):
  params = Params()
  present = usbgpu_present()
  compiled = os.path.isfile(get_manifest_path(modeld_pkl_path(usbgpu=True)))
  if not (present and compiled):
    # no big model to run. idle, do NOT return: a returning process trips the manager's
    # "bigmodeld not running" alert. present vs compiled tells us which one is missing.
    cloudlog.warning(f"bigmodeld idling, no big model (usbgpu_present={present} compiled={compiled})")
    while True:
      time.sleep(1)
  while True:
    while True:
      result = calibrate_usb_gpu_link_result(
        attempts=int(os.getenv("USBGPU_RETRAIN_ATTEMPTS", "1")),
        threshold=float(os.getenv("USBGPU_RETRAIN_THRESHOLD", "10")),
        quick_seconds=float(os.getenv("USBGPU_RETRAIN_QUICK_SECONDS", "5")),
        confirm_seconds=float(os.getenv("USBGPU_RETRAIN_CONFIRM_SECONDS", "0")),
        cloudlog=cloudlog,
      )
      if result.passed:
        break
      try:
        params.put_bool("UsbGpuActive", False)
        params.put_bool("UsbGpuFailed", True)
      except Exception:
        cloudlog.exception("bigmodeld failed to update USB GPU params after retrain failure")
      cloudlog.warning(f"bigmodeld delaying model load: USB GPU link retrain failed after {result.time_to_stable_s:.1f}s")
      time.sleep(float(os.getenv("USBGPU_RETRAIN_RETRY_DELAY", "30")))

    try:
      params.put_bool("UsbGpuFailed", False)
    except Exception:
      cloudlog.exception("bigmodeld failed to update USB GPU params after retrain pass")
    try:
      from openpilot.selfdrive.modeld.model_worker import UsbGpuNeedsReload, run
      run(usbgpu=True, channel_path=BIG_CHANNEL, core=7, priority=53, demo=demo)
    except UsbGpuNeedsReload:
      cloudlog.warning("bigmodeld restarting USB GPU path after offroad hotplug failure")
      time.sleep(float(os.getenv("USBGPU_RELOAD_RETRY_DELAY", "2")))
      continue
    except Exception:
      # any crash before the worker's own model-load/run guards (eg vision/setup phase) must not exit:
      # a returning bigmodeld trips the manager "not running" alert which soft-disables even though
      # small is healthy. park until the next ignition, the selector stays on small.
      cloudlog.exception("bigmodeld crashed, parking until next ignition cycle")
      while True:
        time.sleep(1)


if __name__ == "__main__":
  import argparse
  parser = argparse.ArgumentParser()
  parser.add_argument('--demo', action='store_true')
  args = parser.parse_args()
  try:
    main(demo=args.demo)
  except KeyboardInterrupt:
    cloudlog.warning("bigmodeld got SIGINT")
