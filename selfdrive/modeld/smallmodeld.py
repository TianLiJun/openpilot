#!/usr/bin/env python3
import os

from openpilot.common.swaglog import cloudlog
from openpilot.common.file_chunker import get_manifest_path
from openpilot.selfdrive.modeld.helpers import modeld_pkl_path, usbgpu_present
from openpilot.selfdrive.modeld.model_channel import SMALL_CHANNEL
from openpilot.selfdrive.modeld.model_worker import run


def main(demo=False):
  # Stock/no-eGPU path keeps smallmodeld on core 7 for best standalone reliability. When the USB GPU
  # model is actually available, move small to the little cluster so big can own core 7.
  use_usbgpu = usbgpu_present() and os.path.isfile(get_manifest_path(modeld_pkl_path(usbgpu=True)))
  core = [0, 1, 2, 3] if use_usbgpu else 7
  try:
    run(usbgpu=False, channel_path=SMALL_CHANNEL, core=core, priority=52, demo=demo)
  except Exception:
    cloudlog.exception("smallmodeld crashed")  # the launcher only sends crashes to sentry, log to rlog too
    raise


if __name__ == "__main__":
  import argparse
  parser = argparse.ArgumentParser()
  parser.add_argument('--demo', action='store_true')
  args = parser.parse_args()
  try:
    main(demo=args.demo)
  except KeyboardInterrupt:
    cloudlog.warning("smallmodeld got SIGINT")
