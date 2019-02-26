cmake_minimum_required(VERSION 3.1)

project(wfcroot)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ci)

getlibs(faslib wjson wlog wflow iow wjrpc wrtstat wfc)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/wfc/cmake)

getlibs(wfc_core wfc_io wfc_jsonrpc)

add_library(
  wfcroot
  wfcroot.cpp
)

include(FindThreads)
find_package(Boost COMPONENTS system program_options filesystem date_time regex REQUIRED)

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

target_link_libraries(
  wfcroot 
    ${wfcroot_libraries}
    ${Boost_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
)

add_dependencies(wfcroot ${wfcroot_libraries})

if ( BUILD_TESTING AND STANDALONE )
  enable_testing()
endif()
