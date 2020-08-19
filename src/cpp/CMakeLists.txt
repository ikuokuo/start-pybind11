set(MY_CURR ${CMAKE_CURRENT_LIST_DIR})

# add_my_executable(NAME [SRCS srcs] [LIBS libs] [THREAD])
macro(add_my_executable NAME)
  set(options THREAD)
  set(oneValueArgs)
  set(multiValueArgs SRCS LIBS)
  cmake_parse_arguments(THIS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(THIS_SRCS)
    add_executable(${NAME} ${THIS_SRCS})
  else()
    if(EXISTS ${MY_CURR}/${NAME}.cc)
      set(THIS_SRCS ${NAME}.cc)
    elseif(EXISTS ${MY_CURR}/${NAME}.cpp)
      set(THIS_SRCS ${NAME}.cpp)
    else()
      message(FATAL_ERROR "${NAME}.cc|cpp not found")
    endif()
    add_executable(${NAME} ${THIS_SRCS})
  endif()

  if(THIS_LIBS)
    target_link_libraries(${NAME} ${THIS_LIBS})
  endif()

  if(THIS_THREAD AND THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(${NAME} PUBLIC "-pthread")
  endif()
endmacro()

# add_my_library(NAME [SRCS srcs] [LIBS libs] [SHARED] [THREAD])
macro(add_my_library NAME)
  set(options SHARED THREAD)
  set(oneValueArgs)
  set(multiValueArgs SRCS LIBS)
  cmake_parse_arguments(THIS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  set(__lib_type "STATIC")
  if(THIS_SHARED)
    set(__lib_type "SHARED")
  endif()

  if(THIS_SRCS)
    add_library(${NAME} ${__lib_type} ${THIS_SRCS})
  else()
    if(EXISTS ${MY_CURR}/${NAME}.cc)
      set(THIS_SRCS ${NAME}.cc)
    elseif(EXISTS ${MY_CURR}/${NAME}.cpp)
      set(THIS_SRCS ${NAME}.cpp)
    else()
      message(FATAL_ERROR "${NAME}.cc|cpp not found")
    endif()
    add_library(${NAME} ${__lib_type} ${THIS_SRCS})
  endif()

  if(THIS_LIBS)
    target_link_libraries(${NAME} PUBLIC ${THIS_LIBS})
  endif()

  if(THIS_THREAD AND THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(${NAME} PUBLIC "-pthread")
  endif()

  target_compile_definitions(${NAME} PRIVATE MY_EXPORTS)

  if(MY_VERSION)
    set_target_properties(${NAME} PROPERTIES
      VERSION ${MY_VERSION}
      SOVERSION "${MY_VERSION_MAJOR}.${MY_VERSION_MINOR}"
    )
  endif()
  unset(__lib_type)
endmacro()

add_subdirectory(${MY_CURR}/first_steps)
