cmake_minimum_required(VERSION 3.1)

project(wfcroot)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ci)

add_subdirectory(faslib)
add_subdirectory(wjson)
add_subdirectory(wlog)
add_subdirectory(wflow)
add_subdirectory(wrtstat)
add_subdirectory(iow)
add_subdirectory(wjrpc)
add_subdirectory(wfc)
add_subdirectory(wfc_io)
add_subdirectory(wfc_core)
add_subdirectory(wfc_jsonrpc)

add_library(
  wfcroot
  wfcroot.cpp
)

set(
  wfcroot_libraries
  wfc_jsonrpc
  wfc_io
  wfc_core
  wfc
  wjrpc
  wflow
  iow
  wrtstat
  wlog
)

target_link_libraries(wfcroot ${wfcroot_libraries})
add_dependencies(wfcroot ${wfcroot_libraries})


