set(MY_CURR ${CMAKE_CURRENT_LIST_DIR})

get_filename_component(MY_NAME ${MY_CURR} NAME)
set_outdir(
  ARCHIVE "${MY_OUTPUT}/lib/${MY_NAME}"
  LIBRARY "${MY_OUTPUT}/lib/${MY_NAME}"
  RUNTIME "${MY_OUTPUT}/bin/${MY_NAME}"
)

## targets

add_pb_library(tick_pb LIBS tick SHARED THREAD)

## install

install(TARGETS tick_pb
  EXPORT pybind-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${MY_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MY_NAME}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MY_NAME}
)
