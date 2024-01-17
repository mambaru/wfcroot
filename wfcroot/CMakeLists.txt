add_library(wfcroot wfcroot.cpp)
wci_targets(wfcroot)
target_link_libraries(wfcroot PUBLIC wfc_jsonrpc wfc_io wfc_core wfc)
target_include_directories(wfcroot PUBLIC "$<BUILD_INTERFACE:${wfcroot_SOURCE_DIR}>")
