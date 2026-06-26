#!/usr/bin/env python3
import argparse
import statistics
import sys
import time
from pathlib import Path

from openpilot.selfdrive.modeld.usbgpu_retrain import calibrate_usb_gpu_link_result


def main() -> int:
  parser = argparse.ArgumentParser(description="Retrain and qualify the ASM2464 USB GPU link.")
  parser.add_argument("--attempts", type=int, default=8)
  parser.add_argument("--threshold", type=float, default=10.0, help="maximum confirmed PORTLI delta per second")
  parser.add_argument("--quick-seconds", type=float, default=15.0)
  parser.add_argument("--confirm-seconds", type=float, default=60.0)
  parser.add_argument("--runs", type=int, default=1, help="repeat full calibration and report average time to stable")
  parser.add_argument("--log", type=Path, default=Path("/data/tmp/usb_retrain_search_v2.tsv"))
  parser.add_argument("--snapshot", type=Path, default=Path("/data/tmp/usb_golden_snapshot.txt"))
  args = parser.parse_args()

  passed_times = []
  for run in range(1, args.runs + 1):
    print(f"=== retrain run {run}/{args.runs} ===", flush=True)
    result = calibrate_usb_gpu_link_result(
      attempts=args.attempts,
      threshold=args.threshold,
      quick_seconds=args.quick_seconds,
      confirm_seconds=args.confirm_seconds,
      log_path=args.log,
      snapshot_path=args.snapshot,
    )
    if not result.passed:
      print(f"run {run} failed after {result.time_to_stable_s:.1f}s", flush=True)
      return 1
    passed_times.append(result.time_to_stable_s)
    print(f"run {run} passed in {result.time_to_stable_s:.1f}s attempts={result.attempts} err_per_s={result.err_per_s:.2f}", flush=True)
    if run != args.runs:
      time.sleep(2.0)

  if passed_times:
    avg = statistics.mean(passed_times)
    print(f"summary: runs={len(passed_times)} avg_time_to_stable_s={avg:.1f} min={min(passed_times):.1f} max={max(passed_times):.1f}", flush=True)
  return 0


if __name__ == "__main__":
  sys.exit(main())
