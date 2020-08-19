#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <limits>
#include <thread>

using TickEvent = std::function<void(std::int64_t elapsed_ms)>;
using TickRunCallback = std::function<void()>;

class Tick {
 public:
  using clock = std::chrono::high_resolution_clock;

  Tick(std::int64_t tick_ms,
       std::int64_t life_ms = std::numeric_limits<std::int64_t>::max());
  Tick(TickEvent tick_event, std::int64_t tick_ms,
       std::int64_t life_ms = std::numeric_limits<std::int64_t>::max(),
       TickRunCallback run_beg = nullptr,
       TickRunCallback run_end = nullptr);
  virtual ~Tick();

  bool IsRunning() const;

  void Start();
  void Stop(bool wait_life_over = false);

  const std::chrono::time_point<clock> &GetTimeStart() const;

  void SetTickEvent(TickEvent &&tick_event);
  void SetTickEvent(const TickEvent &tick_event);

  void SetRunBegCallback(TickRunCallback &&run_beg);
  void SetRunBegCallback(const TickRunCallback &run_beg);

  void SetRunEndCallback(TickRunCallback &&run_end);
  void SetRunEndCallback(const TickRunCallback &run_end);

  void WaitLifeOver();

 protected:
  virtual void OnTickEvent(std::int64_t elapsed_ms);
  virtual void OnLifeOver(std::int64_t elapsed_ms);

  void Run();

  TickEvent tick_event_;

  std::int64_t tick_ms_;
  std::int64_t life_ms_;

  TickRunCallback run_beg_;
  TickRunCallback run_end_;

  std::atomic_bool is_running_;
  std::thread thread_;

  std::chrono::time_point<clock> time_start_;
};
