#include <iostream>

#include "tick.h"

int main(int argc, char const *argv[]) {
  (void)argc;
  (void)argv;

  Tick tick([](std::int64_t elapsed_ms) {
    std::cout << "elapsed: " << elapsed_ms << " ms" << std::endl;
  }, 500, 2000);

  tick.Start();
  tick.WaitLifeOver();
  return 0;
}
