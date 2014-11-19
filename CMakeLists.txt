cmake_minimum_required(VERSION 2.6)

project(wfcroot)

include_directories(wfc)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/wfc/cmake")

add_subdirectory(wfc)
add_subdirectory(wfc_startup)
add_subdirectory(wfc_core)
add_subdirectory(wfc_config)
add_subdirectory(wfc_logger)
add_subdirectory(wfc_hub)
add_subdirectory(wfc_repli-hub)
add_subdirectory(wfc_pubsub-service)
add_subdirectory(wfc_pubsub-gateway)



