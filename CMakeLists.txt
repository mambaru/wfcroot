cmake_minimum_required(VERSION 3.1)

project(wfcroot)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ci)

file(GLOB RESULT ${CMAKE_CURRENT_SOURCE_DIR}/wfc)
list(LENGTH RESULT RES_LEN)
if(RES_LEN EQUAL 0)
  execute_process(
    COMMAND 
      git submodule update --init
    WORKING_DIRECTORY 
      ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE
      EXIT_CODE
    ERROR_QUIET
  )
endif()



if ( STANDALONE )
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/wfc/cmake)
endif()



include_directories(faslib)
include_directories(wjson)
include_directories(wlog)
include_directories(wflow)
include_directories(wrtstat)
include_directories(iow)
include_directories(wjrpc)
include_directories(wfc)

set( BUILD_TESTING_OLD ${BUILD_TESTING} )
set( BUILD_TESTING OFF )
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
set( BUILD_TESTING ${BUILD_TESTING_OLD} )

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
