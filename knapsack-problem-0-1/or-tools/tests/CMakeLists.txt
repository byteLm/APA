

add_executable(ORToolsUnitTest "unittests_ortools.cpp")
target_link_libraries(ORToolsUnitTest GTest::GTest GTest::Main ortools::ortools GreedyLib BruteForceLib DPSolverLib  )
