set(MY_CURR ${CMAKE_CURRENT_LIST_DIR})

# pybind

set(MY_PYBIND ${MY_CURR}/third_party/pybind11-2.5.0)

add_subdirectory(${MY_PYBIND})

include_directories(
  ${MY_PYBIND}/include
)

# add_pb_library(NAME [SRCS srcs] [LIBS libs] [SHARED] [THREAD])
macro(add_pb_library NAME)
  set(options SHARED THREAD)
  set(oneValueArgs)
  set(multiValueArgs SRCS LIBS)
  cmake_parse_arguments(THIS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  set(__lib_type "STATIC")
  if(THIS_SHARED)
    set(__lib_type "SHARED")
  endif()

  if(THIS_SRCS)
    pybind11_add_module(${NAME} ${__lib_type} ${THIS_SRCS})
  else()
    if(EXISTS ${MY_CURR}/${NAME}.cc)
      set(THIS_SRCS ${NAME}.cc)
    elseif(EXISTS ${MY_CURR}/${NAME}.cpp)
      set(THIS_SRCS ${NAME}.cpp)
    else()
      message(FATAL_ERROR "${NAME}.cc|cpp not found")
    endif()
    pybind11_add_module(${NAME} ${__lib_type} ${THIS_SRCS})
  endif()
  unset(__lib_type)

  set(__libs ${THIS_LIBS})
  if(THIS_THREAD)
    list(APPEND __libs Threads::Threads)
  endif()
  if(__libs)
    target_link_libraries(${NAME} PUBLIC ${__libs})
  endif()
  unset(__libs)

  target_compile_definitions(${NAME} PRIVATE MY_EXPORTS)

  if(MY_VERSION)
    set_target_properties(${NAME} PROPERTIES
      VERSION ${MY_VERSION}
      SOVERSION "${MY_VERSION_MAJOR}.${MY_VERSION_MINOR}"
    )
  endif()
endmacro()

# targets

add_subdirectory(${MY_CURR}/first_steps)
add_subdirectory(${MY_CURR}/cpp_thread_callback)
