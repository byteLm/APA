cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler")

project(SortAlgorithms)

set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})


# 3rdParty libraries
find_package(GTest REQUIRED)


include_directories("common/")
add_subdirectory("greedy")
add_subdirectory("brute-force")
add_subdirectory("dynamic-programming")

# Application which generates data and runs the sorting algorithms.
add_executable(GenKnapSackData "main_knapsack.cpp")

target_link_libraries(GenKnapSackData PUBLIC GreedyLib BruteForceLib DPSolverLib)


