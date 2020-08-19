#include <pybind11/pybind11.h>

#include "cpp/first_steps/first_steps.h"

namespace py = pybind11;

PYBIND11_MODULE(first_steps_pb, m) {
  m.doc() = "first_steps_pb bindings";

  m.def("add", &add, "A function which adds two numbers");
}
