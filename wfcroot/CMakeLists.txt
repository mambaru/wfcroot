
add_library(wfcroot wfcroot.cpp)

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
