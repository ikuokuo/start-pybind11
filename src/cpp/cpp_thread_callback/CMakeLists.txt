set(MY_CURR ${CMAKE_CURRENT_LIST_DIR})

get_filename_component(MY_NAME ${MY_CURR} NAME)
set_outdir(
  ARCHIVE "${MY_OUTPUT}/lib/${MY_NAME}"
  LIBRARY "${MY_OUTPUT}/lib/${MY_NAME}"
  RUNTIME "${MY_OUTPUT}/bin/${MY_NAME}"
)

## targets

set(my_exe_names
  tick_test
)

foreach(my_name IN LISTS my_exe_names)
  add_my_executable(${my_name}
    SRCS ${my_name}.cc tick.cc
    THREAD
  )
endforeach()

set(my_lib_names
  tick
)

foreach(my_name IN LISTS my_lib_names)
  add_my_library(${my_name} SHARED THREAD)
endforeach()

## install

install(TARGETS ${my_exe_names} ${my_lib_names}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${MY_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MY_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MY_NAME}
)
