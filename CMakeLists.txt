cmake_minimum_required(VERSION 3.1)

project(wfcroot)

include(cmake/ci.cmake)

getlibs(faslib wjson wlog wflow iow wjrpc wrtstat wfc)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/wfc/cmake)
getlibs(wfc_core wfc_io wfc_jsonrpc)

add_subdirectory(wfcroot)

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory(tests)
endif()
