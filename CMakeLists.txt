cmake_minimum_required(VERSION 2.6)

project(wfcroot)

if ( NOT WFC_READY )
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/wfc/cmake")
  include(Wfc)
endif()

include_directories(wfc)
include_directories(iow)
include_directories(faslib)

add_subdirectory(faslib)
add_subdirectory(iow)
add_subdirectory(wfc)
add_subdirectory(wfc_core)
add_subdirectory(wfc_io)
add_subdirectory(wfc_jsonrpc)

include(Wfc)

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
)

target_link_libraries(wfcroot ${wfcroot_libraries})
add_dependencies(wfcroot ${wfcroot_libraries})
