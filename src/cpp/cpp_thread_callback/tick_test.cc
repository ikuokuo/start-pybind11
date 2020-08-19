#include <iostream>

#include "tick.h"

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;

  Tick tick(500, 5000);

  tick.SetTickEvent([&tick](std::int64_t elapsed_ms) {
    std::cout << "elapsed: " << elapsed_ms << " ms" << std::endl;
    if (elapsed_ms >= 2000) {
      tick.Stop();
    }
  });

  tick.Start();
  tick.WaitLifeOver();
  return 0;
}
