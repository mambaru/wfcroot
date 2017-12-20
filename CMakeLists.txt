cmake_minimum_required(VERSION 2.6)

project(wfcroot)

if ( NOT WFC_READY )
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/wfc/cmake")
  include(Wfc)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wfc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/iow)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wjson)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wlog)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wjrpc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/faslib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wrtstat)

add_subdirectory(faslib)
add_subdirectory(wjson)
add_subdirectory(wlog)
add_subdirectory(wrtstat)
add_subdirectory(iow)
add_subdirectory(wjrpc)
add_subdirectory(wfc)
add_subdirectory(wfc_io)
add_subdirectory(wfc_core)
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
  wjrpc
  wrtstat
  wlog
)

target_link_libraries(wfcroot ${wfcroot_libraries})
add_dependencies(wfcroot ${wfcroot_libraries})
