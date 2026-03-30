

add_executable(DPSolverUnitTest "unittests_dpsolver.cpp")
target_link_libraries(DPSolverUnitTest GTest::GTest GTest::Main DPSolverLib)
