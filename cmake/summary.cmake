# summary

status("")
status("Platform:")
status("  HOST_OS: ${HOST_OS}")
status("  HOST_ARCH: ${HOST_ARCH}")
status("  HOST_COMPILER: ${CMAKE_CXX_COMPILER_ID}")
status("    COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")

status("")
status("Build:")
status("  Python: " IF BUILD_PYTHON_BINDINGS "YES" ELSE "NO")

status("")
