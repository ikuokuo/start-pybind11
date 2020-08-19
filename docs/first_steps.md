# First Steps

## Preparation

### pybind11

```bash
cd start-pybind11/
git submodule update --init

# git submodule add https://github.com/pybind/pybind11.git src/pybind/third_party/pybind11-2.5.0
# cd src/pybind/third_party/pybind11-2.5.0/
# git checkout tags/v2.5.0
```

<!--
CMake Error at src/pybind/CMakeLists.txt:4 (add_subdirectory):
  add_subdirectory not given a binary directory but the given source
  directory
  "/home/john/Codes/ikuokuo/start-pybind11/third_party/pybind11-2.5.0" is not
  a subdirectory of "/home/john/Codes/ikuokuo/start-pybind11/src/pybind".
  When specifying an out-of-tree source a binary directory must be explicitly
  specified.
-->

## Coding

* [first_steps.h](../src/cpp/first_steps/first_steps.h)
* [first_steps.cc](../src/cpp/first_steps/first_steps.cc)
* [first_steps_pb.cc](../src/pybind/first_steps/first_steps_pb.cc)

## Build

```bash
cd start-pybind11/
make install
```

```bash
_install/
└── lib
    └── first_steps
        ├── first_steps_pb.cpython-37m-x86_64-linux-gnu.so -> first_steps_pb.cpython-37m-x86_64-linux-gnu.so.0.1
        ├── first_steps_pb.cpython-37m-x86_64-linux-gnu.so.0.1 -> first_steps_pb.cpython-37m-x86_64-linux-gnu.so.0.1.0
        ├── first_steps_pb.cpython-37m-x86_64-linux-gnu.so.0.1.0
        ├── libfirst_steps.so -> libfirst_steps.so.0.1
        ├── libfirst_steps.so.0.1 -> libfirst_steps.so.0.1.0
        └── libfirst_steps.so.0.1.0
```

## Run

```bash
$ source setup.bash first_steps
LD_LIBRARY_PATH, PYTHONPATH
+ /home/john/Codes/ikuokuo/start-pybind11/_install/lib/first_steps
```

```bash
$ python
Python 3.7.4 (default, Aug 13 2019, 20:35:49)
[GCC 7.3.0] :: Anaconda, Inc. on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import first_steps_pb as pb
>>> pb.add(1, 2)
3
```
