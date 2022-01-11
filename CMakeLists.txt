cmake_minimum_required(VERSION 3.1)

project(wfcroot)

set(BUILD_TESTING OFF)

include(cmake/ci.cmake)

wci_submodule(NAME wfc SUPERMODULE )
wci_submodule(NAME wfc_core )
wci_submodule(NAME wfc_io )
wci_submodule(NAME wfc_jsonrpc )

add_subdirectory(wfcroot)

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
endif()
