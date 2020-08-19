#!/usr/bin/env python
# -*- coding: utf-8 -*-
# pylint: disable=missing-docstring
import tick_pb as tick

if __name__ == "__main__":
  t = tick.Tick(500, 1000)
  t.set_tick_event(lambda elapsed_ms: print(f"elapsed: {elapsed_ms} ms"))
  t.set_run_beg_callback(lambda: print("run beg"))
  t.set_run_end_callback(lambda: print("run end"))
  t.start()
  t.wait_life_over()

  t = tick.Tick(lambda elapsed_ms: print(f"elapsed: {elapsed_ms} ms"),
                500, 1000,
                lambda: print("run beg"), lambda: print("run end"))
  t.start()
  t.wait_life_over()
