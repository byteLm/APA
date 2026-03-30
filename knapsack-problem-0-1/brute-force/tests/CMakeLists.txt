

add_executable(BruteForceUnitTest "unittests_brute_force.cpp")
target_link_libraries(BruteForceUnitTest GTest::GTest GTest::Main BruteForceLib)
