cmake_minimum_required(VERSION 3.1)
project(start-pybind11 VERSION 0.1.0 LANGUAGES C CXX)

include(cmake/global.cmake)

set(MY_ROOT ${PROJECT_SOURCE_DIR})

set(MY_VERSION ${PROJECT_VERSION})
set_version_values(MY_VERSION)

# cmake options

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# flags

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wformat")
if(NOT HOST_OS STREQUAL "Win")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

string(STRIP "${CMAKE_CXX_FLAGS}" CMAKE_CXX_FLAGS)
status("CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

# packages

LIST(APPEND CMAKE_MODULE_PATH "${MY_ROOT}/cmake/modules")

## threads

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# targets

set(MY_OUTPUT "${MY_ROOT}/_output")
set_outdir(
  ARCHIVE "${MY_OUTPUT}/lib"
  LIBRARY "${MY_OUTPUT}/lib"
  RUNTIME "${MY_OUTPUT}/bin"
)

include_directories(
  include
  src
)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(CMAKE_MACOSX_RPATH 1)
#set(CMAKE_INSTALL_RPATH "${MY_CMAKE_RPATH}")

## cpp

add_subdirectory(src/cpp)

## pybind

if(BUILD_PYTHON_BINDINGS)
  add_subdirectory(src/pybind)
endif()

# summary

include(cmake/summary.cmake)

configure_file(setup.bash.in ${MY_ROOT}/setup.bash @ONLY)
