

include_directories("includes/") 
add_library(DPSolverLib "src/DPSolver.cpp")
target_include_directories(DPSolverLib PUBLIC "includes/") 

target_include_directories(DPSolverLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(DPSolverLib PUBLIC cxx_std_17)

add_subdirectory("tests/")