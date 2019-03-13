
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${UNIT_TEST_BIN_OUTPUT_DIR})                                                                                                                  

add_executable(
  package_test
    package_suite.cpp
    package_test.cpp
    ${FAS_TESTING_CPP}
)

target_link_libraries(package_test wfcroot)
add_test(NAME package_test COMMAND wfcroot)


