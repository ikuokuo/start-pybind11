#include "tick.h"

#include <utility>

Tick::Tick(std::int64_t tick_ms, std::int64_t life_ms)
  : Tick(nullptr, tick_ms, life_ms) {
}

Tick::Tick(TickEvent tick_event, std::int64_t tick_ms, std::int64_t life_ms,
    TickRunCallback run_beg, TickRunCallback run_end)
  : tick_event_(tick_event), tick_ms_(tick_ms), life_ms_(life_ms),
    run_beg_(run_beg), run_end_(run_end),
    is_running_(false) {
}

Tick::~Tick() {
  Stop();
}

bool Tick::IsRunning() const {
  return is_running_;
}

void Tick::Start() {
  if (is_running_) Stop();
  is_running_ = true;
  time_start_ = clock::now();
  thread_ = std::thread(&Tick::Run, this);
}

void Tick::Stop(bool wait_life_over) {
  if (!is_running_) return;
  is_running_ = false;
  if (wait_life_over) {
    WaitLifeOver();
  }
}

const std::chrono::time_point<Tick::clock> &Tick::GetTimeStart() const {
  return time_start_;
}

void Tick::SetTickEvent(TickEvent &&tick_event) {
  tick_event_ = std::move(tick_event);
}

void Tick::SetTickEvent(const TickEvent &tick_event) {
  tick_event_ = tick_event;
}

void Tick::SetRunBegCallback(TickRunCallback &&run_beg) {
  run_beg_ = std::move(run_beg);
}

void Tick::SetRunBegCallback(const TickRunCallback &run_beg) {
  run_beg_ = run_beg;
}

void Tick::SetRunEndCallback(TickRunCallback &&run_end) {
  run_end_ = std::move(run_end);
}

void Tick::SetRunEndCallback(const TickRunCallback &run_end) {
  run_end_ = run_end;
}

void Tick::WaitLifeOver() {
  if (thread_.joinable()) {
    thread_.join();
  }
}

void Tick::OnTickEvent(std::int64_t elapsed_ms) {
  if (tick_event_) {
    tick_event_(elapsed_ms);
  }
}

void Tick::OnLifeOver(std::int64_t /*elapsed_ms*/) {
}

void Tick::Run() {
  if (run_beg_) run_beg_();

  using namespace std::chrono;  // NOLINT

  auto tick_beg = time_start_;
  auto tick_duration = milliseconds(tick_ms_);

  while (is_running_) {
    auto time_elapsed_ms = duration_cast<milliseconds>(
        clock::now() - time_start_).count();
    if (time_elapsed_ms > life_ms_) {
      OnLifeOver(time_elapsed_ms);
      break;
    }

    OnTickEvent(time_elapsed_ms);
    if (!is_running_) break;

    auto tick_end_actual = clock::now();
    auto tick_end_expected = tick_beg + tick_duration;
    auto tick_sleep_time = tick_end_expected - tick_end_actual;
    tick_beg = tick_end_expected;
    // if we've taken too much time we won't sleep
    if (tick_sleep_time <= clock::duration(0)) {
      if (tick_end_actual > tick_end_expected + tick_duration) {
        tick_beg = tick_end_actual;
      }
      continue;
    }
    std::this_thread::sleep_for(tick_sleep_time);
  }

  if (run_end_) run_end_();
}
