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
add_subdirectory(wfc_startup)
add_subdirectory(wfc_config)
add_subdirectory(wfc_core)
add_subdirectory(wfc_logger)
add_subdirectory(wfc_server)
add_subdirectory(wfc_client)
add_subdirectory(wfc_jsonrpc)

include(Wfc)

add_library(
  wfcroot STATIC
  wfcroot.cpp
)

set(
  wfcroot_libraries
  wfc_jsonrpc
  wfc_client
  wfc_server
  wfc_logger
  wfc_core
  wfc_config
  wfc_startup
  wfc
)

target_link_libraries(wfcroot ${wfcroot_libraries})
add_dependencies(wfcroot ${wfcroot_libraries})
