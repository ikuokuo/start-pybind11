#!/usr/bin/env python
# -*- coding: utf-8 -*-
# pylint: disable=missing-docstring, import-error
import functools

import tick_pb as tick


def _main():
  t = tick.Tick(lambda elapsed_ms: print(f"elapsed: {elapsed_ms} ms"),
                500, 1000,
                lambda: print("run beg"), lambda: print("run end"))
  t.start()
  t.wait_life_over()

  print()

  t = tick.Tick(500, 2000)

  def tick_event(t, elapsed_ms):
    print(f"elapsed: {elapsed_ms} ms")
    t.stop()

  t.set_tick_event(functools.partial(tick_event, t))
  t.set_run_beg_callback(lambda: print("run beg"))
  t.set_run_end_callback(lambda: print("run end"))

  t.start()
  t.wait_life_over()


if __name__ == "__main__":
  _main()
