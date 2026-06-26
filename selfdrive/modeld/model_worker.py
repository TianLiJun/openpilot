#!/usr/bin/env python3
import os
os.environ['GMMU'] = '0'  # for usbgpu fast loading, noop for qcom
import json
import time
from pathlib import Path
import numpy as np
import cereal.messaging as messaging
from cereal import car, log
from cereal.messaging import SubMaster
from msgq.visionipc import VisionIpcClient, VisionStreamType
from opendbc.car.car_helpers import get_demo_car_params
from openpilot.common.file_chunker import get_existing_chunks
from openpilot.common.swaglog import cloudlog
from openpilot.common.params import Params
from openpilot.common.filter_simple import FirstOrderFilter
from openpilot.common.realtime import config_realtime_process, DT_MDL
from openpilot.common.transformations.camera import DEVICE_CAMERAS
from openpilot.common.transformations.model import get_warp_matrix
from openpilot.selfdrive.controls.lib.desire_helper import DesireHelper
from openpilot.selfdrive.modeld.constants import ModelConstants
from openpilot.selfdrive.modeld.modeld import ModelState, FrameMeta, LAT_SMOOTH_SECONDS, LONG_SMOOTH_SECONDS
from openpilot.selfdrive.modeld.model_channel import ModelChannel, SMALL_CHANNEL
from openpilot.selfdrive.modeld.helpers import modeld_pkl_path

BIG_LOAD_RETRY_DELAY_S = 5.0
USB_PORTLI_PATH = Path("/sys/devices/platform/soc/a600000.ssusb/portli")
USBGPU_MODEL_LOAD_METRICS = Path("/data/tmp/usbgpu_model_load_metrics.json")
USBGPU_PREWARM = os.getenv("USBGPU_PREWARM", "0") == "1"
USBGPU_SYNTHETIC_WARMUP = os.getenv("USBGPU_SYNTHETIC_WARMUP", "0") == "1"


class UsbGpuNeedsReload(Exception):
  pass


class SyntheticVisionBuf:
  def __init__(self, size: int):
    self.data = bytearray(size)


def synthetic_warm_model(name: str, model: ModelState) -> None:
  bufs = {n: SyntheticVisionBuf(model.frame_buf_params[n][3]) for n in model.vision_input_names}
  transforms = {n: np.eye(3, dtype=np.float32) for n in model.vision_input_names}
  inputs = {
    'desire_pulse': np.zeros(ModelConstants.DESIRE_LEN, dtype=np.float32),
    'traffic_convention': np.array([1.0, 0.0], dtype=np.float32),
    'action_t': np.zeros(2, dtype=np.float32),
  }
  st = time.monotonic()
  model.run(bufs, transforms, inputs, False)
  cloudlog.warning(f"{name} synthetic warmup completed in {time.monotonic() - st:.1f}s at {model.cam_w}x{model.cam_h}")


def connect_vision_clients(name: str):
  cloudlog.warning(f"{name} waiting for camerad vision")
  while True:
    available_streams = VisionIpcClient.available_streams("camerad", block=False)
    if available_streams:
      use_extra_client = VisionStreamType.VISION_STREAM_WIDE_ROAD in available_streams and VisionStreamType.VISION_STREAM_ROAD in available_streams
      main_wide_camera = VisionStreamType.VISION_STREAM_ROAD not in available_streams
      break
    time.sleep(.1)

  vipc_client_main_stream = VisionStreamType.VISION_STREAM_WIDE_ROAD if main_wide_camera else VisionStreamType.VISION_STREAM_ROAD
  vipc_client_main = VisionIpcClient("camerad", vipc_client_main_stream, True)
  vipc_client_extra = VisionIpcClient("camerad", VisionStreamType.VISION_STREAM_WIDE_ROAD, False)
  while not vipc_client_main.connect(False):
    time.sleep(0.1)
  while use_extra_client and not vipc_client_extra.connect(False):
    time.sleep(0.1)
  cloudlog.warning(f"{name} vision connected: main={vipc_client_main.width}x{vipc_client_main.height} extra={use_extra_client}")
  return use_extra_client, main_wide_camera, vipc_client_main, vipc_client_extra


def read_usb_portli() -> int | None:
  try:
    return int(USB_PORTLI_PATH.read_text().strip(), 16)
  except Exception:
    return None


def log_usb_portli_rate(name: str, stage: str, start: int | None, start_t: float, end: int | None = None) -> int | None:
  if start is None:
    return end
  end = read_usb_portli() if end is None else end
  if end is None:
    return None
  dt = max(time.monotonic() - start_t, 0.001)
  delta = end - start if end >= start else end
  cloudlog.warning(f"{name} USB link {stage}: portli=0x{start:08x}->0x{end:08x} delta={delta} seconds={dt:.1f} err_per_s={delta / dt:.2f}")
  return end


def chunked_file_size(path: Path) -> int | None:
  try:
    return sum(Path(p).stat().st_size for p in get_existing_chunks(path))
  except Exception:
    return None


def write_usbgpu_load_metrics(model_bytes: int, load_s: float) -> None:
  try:
    USBGPU_MODEL_LOAD_METRICS.parent.mkdir(parents=True, exist_ok=True)
    USBGPU_MODEL_LOAD_METRICS.write_text(json.dumps({
      "bytes": model_bytes,
      "mib": model_bytes / (1024 * 1024),
      "seconds": load_s,
      "mibps": model_bytes / (1024 * 1024) / max(load_s, 0.001),
      "monotonic": time.monotonic(),
      "wall_time": time.strftime("%Y-%m-%dT%H:%M:%S%z"),
    }, sort_keys=True) + "\n")
  except Exception:
    cloudlog.exception("failed to write USB GPU model load metrics")


def safe_put_bool(params: Params, key: str, value: bool) -> None:
  try:
    params.put_bool(key, value)
  except Exception:
    cloudlog.exception(f"failed to write param {key}")


def run(usbgpu: bool, channel_path: str, core, priority: int = 53, demo=False):
  name = "bigmodeld" if usbgpu else "smallmodeld"
  cloudlog.warning(f"{name} init")
  # Big is isolated on core 7 while small runs on cores 0-3, so let big load/warm at full priority.
  # Keeping this configurable makes it easy to back off if a platform shows startup contention.
  load_priority = int(os.getenv("USBGPU_LOAD_PRIORITY", str(priority))) if usbgpu else priority
  config_realtime_process(core, load_priority)
  params = Params()
  channel = ModelChannel(channel_path, create=True)

  model = None
  if usbgpu and USBGPU_PREWARM:
    st = time.monotonic()
    load_portli = read_usb_portli()
    try:
      model_bytes = chunked_file_size(modeld_pkl_path(True))
      cloudlog.warning(f"{name} prewarming model before camerad")
      model = ModelState(None, None, True)
      load_s = time.monotonic() - st
      if model_bytes is not None:
        write_usbgpu_load_metrics(model_bytes, load_s)
        cloudlog.warning(
          f"{name} prewarm model load throughput: bytes={model_bytes} MiB={model_bytes / (1024 * 1024):.1f} "
          f"seconds={load_s:.2f} MiBps={model_bytes / (1024 * 1024) / max(load_s, 0.001):.2f}"
        )
      log_usb_portli_rate(name, "prewarm_model_load", load_portli, st)
      if USBGPU_SYNTHETIC_WARMUP:
        synthetic_warm_model(name, model)
      safe_put_bool(params, "UsbGpuFailed", False)
    except Exception:
      log_usb_portli_rate(name, "prewarm_failed", load_portli, st)
      cloudlog.exception(f"{name} prewarm failed, falling back to onroad load")
      model = None

  use_extra_client, main_wide_camera, vipc_client_main, vipc_client_extra = connect_vision_clients(name)

  load_attempt = 0
  while True:
    load_attempt += 1
    st = time.monotonic()
    load_portli = read_usb_portli() if usbgpu else None
    cloudlog.warning(f"{name} loading model (attempt {load_attempt})")
    try:
      model_bytes = chunked_file_size(modeld_pkl_path(usbgpu)) if usbgpu else None
      if model is None or model.cam_w != vipc_client_main.width or model.cam_h != vipc_client_main.height:
        model = ModelState(vipc_client_main.width, vipc_client_main.height, usbgpu)
      load_s = time.monotonic() - st
      if usbgpu and model_bytes is not None:
        write_usbgpu_load_metrics(model_bytes, load_s)
        cloudlog.warning(
          f"{name} model load throughput: bytes={model_bytes} MiB={model_bytes / (1024 * 1024):.1f} "
          f"seconds={load_s:.2f} MiBps={model_bytes / (1024 * 1024) / max(load_s, 0.001):.2f}"
        )
      if usbgpu:
        log_usb_portli_rate(name, "model_load", load_portli, st)
      if usbgpu:
        safe_put_bool(params, "UsbGpuFailed", False)
      cloudlog.warning(f"{name} loaded model in {load_s:.1f}s after {load_attempt} attempt(s)")
      break
    except Exception:
      if usbgpu:
        log_usb_portli_rate(name, "model_load_failed", load_portli, st)
      cloudlog.exception(f"{name} model load failed on attempt {load_attempt}")
      if not usbgpu:
        raise  # small is the pacer, let it crash so the manager restarts it
      # Big load failure is not fatal to driving: selector is paced by smallmodeld. Keep this
      # process alive and keep trying, but make the UI clear that the eGPU model is not usable yet.
      safe_put_bool(params, "UsbGpuActive", False)
      safe_put_bool(params, "UsbGpuFailed", True)
      time.sleep(BIG_LOAD_RETRY_DELAY_S)

  sm = SubMaster(["deviceState", "carState", "roadCameraState", "liveCalibration", "driverMonitoringState", "carControl", "liveDelay"])
  if demo:
    CP = get_demo_car_params()
  else:
    CP = messaging.log_from_bytes(params.get("CarParams", block=True), car.CarParams)
  long_delay = CP.longitudinalActuatorDelay + LONG_SMOOTH_SECONDS
  DH = DesireHelper()
  frame_dropped_filter = FirstOrderFilter(0., 10., 1. / ModelConstants.MODEL_RUN_FREQ)

  model_transform_main = np.zeros((3, 3), dtype=np.float32)
  model_transform_extra = np.zeros((3, 3), dtype=np.float32)
  live_calib_seen = False
  buf_main, buf_extra = None, None
  meta_main = FrameMeta()
  meta_extra = FrameMeta()
  last_vipc_frame_id = 0
  run_count = 0
  produced_count = 0
  big_warmed = False
  last_frame_log = 0.0
  warmup_portli = read_usb_portli() if usbgpu else None
  warmup_start_t = time.monotonic()
  steady_portli = warmup_portli
  steady_start_t = warmup_start_t
  no_frame_start_t = None

  while True:
    while meta_main.timestamp_sof < meta_extra.timestamp_sof + 25000000:
      buf_main = vipc_client_main.recv()
      meta_main = FrameMeta(vipc_client_main)
      if buf_main is None:
        break
    if buf_main is None:
      # no frame from camerad. if this persists the camera pipeline is wedged, which stalls both models
      now = time.monotonic()
      if no_frame_start_t is None:
        no_frame_start_t = now
      if now - last_frame_log > 2.0:
        cloudlog.warning(f"{name} no camera frame from camerad, waiting")
        last_frame_log = now
      if usbgpu and now - no_frame_start_t > 2.0:
        cloudlog.warning(f"{name} reconnecting camerad vision after {now - no_frame_start_t:.1f}s without frames")
        use_extra_client, main_wide_camera, vipc_client_main, vipc_client_extra = connect_vision_clients(name)
        if model.cam_w != vipc_client_main.width or model.cam_h != vipc_client_main.height:
          cloudlog.warning(f"{name} camera dimensions changed, reloading model")
          model = ModelState(vipc_client_main.width, vipc_client_main.height, usbgpu)
        meta_main = FrameMeta()
        meta_extra = FrameMeta()
        last_vipc_frame_id = 0
        no_frame_start_t = None
      continue
    no_frame_start_t = None

    if use_extra_client:
      while True:
        buf_extra = vipc_client_extra.recv()
        meta_extra = FrameMeta(vipc_client_extra)
        if buf_extra is None or meta_main.timestamp_sof < meta_extra.timestamp_sof + 25000000:
          break
      if buf_extra is None:
        continue
    else:
      buf_extra = buf_main
      meta_extra = meta_main

    sm.update(0)
    desire = DH.desire
    is_rhd = sm["driverMonitoringState"].isRHD
    frame_id = sm["roadCameraState"].frameId
    v_ego = max(sm["carState"].vEgo, 0.)
    lat_delay = sm["liveDelay"].lateralDelay + LAT_SMOOTH_SECONDS
    if sm.updated["liveCalibration"] and sm.seen['roadCameraState'] and sm.seen['deviceState']:
      device_from_calib_euler = np.array(sm["liveCalibration"].rpyCalib, dtype=np.float32)
      dc = DEVICE_CAMERAS[(str(sm['deviceState'].deviceType), str(sm['roadCameraState'].sensor))]
      model_transform_main = get_warp_matrix(device_from_calib_euler, dc.ecam.intrinsics if main_wide_camera else dc.fcam.intrinsics, False).astype(np.float32)
      model_transform_extra = get_warp_matrix(device_from_calib_euler, dc.ecam.intrinsics, True).astype(np.float32)
      live_calib_seen = True

    traffic_convention = np.zeros(2)
    traffic_convention[int(is_rhd)] = 1
    vec_desire = np.zeros(ModelConstants.DESIRE_LEN, dtype=np.float32)
    if desire >= 0 and desire < ModelConstants.DESIRE_LEN:
      vec_desire[desire] = 1

    vipc_dropped_frames = max(0, meta_main.frame_id - last_vipc_frame_id - 1)
    frames_dropped = frame_dropped_filter.update(min(vipc_dropped_frames, 10))
    if run_count < 10:
      frame_dropped_filter.x = 0.
      frames_dropped = 0.
    run_count += 1
    frame_drop_ratio = frames_dropped / (1 + frames_dropped)
    prepare_only = vipc_dropped_frames > 0

    bufs = {n: buf_extra if 'big' in n else buf_main for n in model.vision_input_names}
    transforms = {n: model_transform_extra if 'big' in n else model_transform_main for n in model.vision_input_names}
    frame_delay = DT_MDL
    action_delay = DT_MDL / 2
    lat_action_t = lat_delay + frame_delay + action_delay
    long_action_t = long_delay + frame_delay + action_delay
    inputs = {
      'desire_pulse': vec_desire,
      'traffic_convention': traffic_convention,
      'action_t': np.array([lat_action_t, long_action_t], dtype=np.float32),
    }

    mt1 = time.perf_counter()
    try:
      model_output = model.run(bufs, transforms, inputs, prepare_only)
    except Exception:
      cloudlog.exception(f"{name} model run failed")
      if not usbgpu:
        raise  # small is the pacer, let it crash so the manager restarts it
      if not params.get_bool("IsEngaged"):
        safe_put_bool(params, "UsbGpuActive", False)
        safe_put_bool(params, "UsbGpuFailed", True)
        cloudlog.warning(f"{name} failed while not engaged; requesting USB GPU retrain and model reload")
        raise UsbGpuNeedsReload
      # big errored/disconnected. modeld is already on small with no gap. park instead of exiting
      # (exiting trips "bigmodeld not running") and don't touch the usbgpu again until next ignition.
      # flag failed so the UI shows small, not "big: loading"
      safe_put_bool(params, "UsbGpuActive", False)
      safe_put_bool(params, "UsbGpuFailed", True)
      while True:
        time.sleep(1)
    model_execution_time = time.perf_counter() - mt1
    if model_output is not None:
      if usbgpu and not big_warmed:
        steady_portli = log_usb_portli_rate(name, "first_run", warmup_portli, warmup_start_t)
        steady_start_t = time.monotonic()
        # the first full run compiled the tinygrad kernels at low priority so small stayed protected.
        # big is warm now, so take full priority and lead on core 7.
        config_realtime_process(core, priority)
        big_warmed = True
      desire_state = model_output['desire_state'][0].reshape(-1)
      lane_change_prob = desire_state[log.Desire.laneChangeLeft] + desire_state[log.Desire.laneChangeRight]
      DH.update(sm['carState'], sm['carControl'].latActive, lane_change_prob)
      payload = {
        'output': model_output,
        'frame_id': meta_main.frame_id,
        'frame_id_extra': meta_extra.frame_id,
        'road_frame_id': frame_id,
        'timestamp_eof': meta_main.timestamp_eof,
        'vipc_dropped_frames': vipc_dropped_frames,
        'frame_drop_ratio': frame_drop_ratio,
        'live_calib_seen': live_calib_seen,
        'lat_action_t': lat_action_t,
        'long_action_t': long_action_t,
        'v_ego': v_ego,
        'model_execution_time': model_execution_time,
        'lane_change_state': int(DH.lane_change_state),
        'lane_change_direction': int(DH.lane_change_direction),
      }
      channel.write(meta_main.frame_id, payload)
      produced_count += 1
      # heartbeat in the rlog so we see the worker is producing and how fast. a worker that loads but
      # never produces shows a "loaded model" line and no "producing" line
      if produced_count == 1 or produced_count % 100 == 0:
        msg = f"{name} producing: frame={meta_main.frame_id} exec={model_execution_time * 1e3:.0f}ms"
        cloudlog.warning(f"{msg} dropped={vipc_dropped_frames} count={produced_count}")
        if usbgpu and produced_count % 100 == 0:
          steady_portli = log_usb_portli_rate(name, "steady_100_frames", steady_portli, steady_start_t)
          steady_start_t = time.monotonic()
    last_vipc_frame_id = meta_main.frame_id
