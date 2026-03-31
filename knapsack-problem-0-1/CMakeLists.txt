cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler")

project(SortAlgorithms)

set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})


# 3rdParty libraries
find_package(GTest REQUIRED)
find_package(ortools CONFIG REQUIRED)


include_directories("common/")
include_directories("3rdParty/")

add_subdirectory("greedy")
add_subdirectory("brute-force")
add_subdirectory("dynamic-programming")
add_subdirectory("or-tools/tests") # just tests

# Application which generates data and runs the sorting algorithms.
add_executable(GenKnapSackData "main_knapsack.cpp")

target_link_libraries(GenKnapSackData PUBLIC GreedyLib BruteForceLib DPSolverLib ortools::ortools)


