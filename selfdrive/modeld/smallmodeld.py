#!/usr/bin/env python3
from openpilot.common.swaglog import cloudlog
from openpilot.selfdrive.modeld.model_channel import SMALL_CHANNEL
from openpilot.selfdrive.modeld.model_worker import run


def main(demo=False):
  # little cluster (cores 0-3), separate from big on core 7. small is light (qcom, no usb) and
  # holds a steady 20Hz here independent of the big model, so a big-model stall on core 7 no
  # longer starves the small fallback (which was causing modelV2 gaps -> selfdrivedLagging).
  try:
    run(usbgpu=False, channel_path=SMALL_CHANNEL, core=[0,1,2,3], priority=52, demo=demo)
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
