cmake_minimum_required(VERSION 3.1)

project(wfcroot)

#include_directories(faslib)
#include_directories(wjson)
#include_directories(wlog)
#include_directories(wflow)
#include_directories(wrtstat)
#include_directories(iow)
#include_directories(wjrpc)
#include_directories(wfc)
include(wfc)

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


