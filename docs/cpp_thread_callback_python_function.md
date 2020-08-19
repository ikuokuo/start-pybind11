# C++ Thread Callback Python Function

## Coding

* [tick.h](../src/cpp/cpp_thread_callback/tick.h)
* [tick.cc](../src/cpp/cpp_thread_callback/tick.cc)
* [tick_test.cc](../src/cpp/cpp_thread_callback/tick_test.cc)
* [tick_pb.cc](../src/pybind/cpp_thread_callback/tick_pb.cc)
* [tick_test.py](../src/pybind/cpp_thread_callback/tick_test.py)

## Build

```bash
cd start-pybind11/
git submodule update --init

make install
```

## C++ Tick

```bash
$ ./_output/bin/cpp_thread_callback/tick_test
elapsed: 0 ms
elapsed: 500 ms
elapsed: 1000 ms
elapsed: 1500 ms
elapsed: 2000 ms
```

## Python Tick

```bash
$ source setup.bash cpp_thread_callback
LD_LIBRARY_PATH, PYTHONPATH
+ /home/john/Codes/ikuokuo/start-pybind11/_install/lib/cpp_thread_callback
```

```bash
$ python src/pybind/cpp_thread_callback/tick_test.py
run beg
elapsed: 0 ms
elapsed: 500 ms
elapsed: 1000 ms
run end
```
