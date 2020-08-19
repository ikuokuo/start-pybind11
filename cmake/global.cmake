include(${CMAKE_CURRENT_LIST_DIR}/common/include_guard.cmake)
cmake_include_guard()

# macros

include(${CMAKE_CURRENT_LIST_DIR}/global_macros.cmake)

# env

include(${CMAKE_CURRENT_LIST_DIR}/common/target_arch.cmake)
target_architecture(HOST_ARCH)

if(MSVC OR MSYS OR MINGW)
  set(HOST_OS Win)
  set(HOST_OS_WIN true)
elseif(APPLE)
  set(HOST_OS Mac)
  set(HOST_OS_MAC true)
elseif(UNIX)
  set(HOST_OS Linux)
  set(HOST_OS_LINUX true)
else()
  message(FATAL_ERROR "Unsupported OS")
endif()

# options

include(${CMAKE_CURRENT_LIST_DIR}/global_options.cmake)
