cmake_minimum_required(VERSION 2.6)

project(wfcroot)

include_directories(wfc)
include_directories(iow)

if ( NOT CMAKE_MODULE_PATH )
  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/wfc/cmake)
endif()

add_subdirectory(iow)
add_subdirectory(wfc)
add_subdirectory(wfc_startup)
add_subdirectory(wfc_config)
add_subdirectory(wfc_core)
add_subdirectory(wfc_logger)
#add_subdirectory(wfc_hub)
#add_subdirectory(wfc_broker)
#add_subdirectory(wfc_repli-hub)
#add_subdirectory(wfc_pubsub-service)
#add_subdirectory(wfc_pubsub-gateway)

include(Wfc)

add_library(
  wfcroot STATIC
  wfcroot.cpp
)

set(
  wfcroot_libraries 
  wfc_logger
  wfc_core 
  wfc_config 
  wfc_startup 
  wfc 
)

target_link_libraries(wfcroot ${wfcroot_libraries})
add_dependencies(wfcroot ${wfcroot_libraries})
