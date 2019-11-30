add_executable(package_test package_suite.cpp package_test.cpp)
target_link_libraries(package_test PRIVATE wfcroot fas::testing)
wci_test(TARGET package_test COMMAND package_test)


