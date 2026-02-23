cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler")

project(SortAlgorithms)

set(CMAKE_CXX_STANDARD 17)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})


# 3rdParty libraries
find_package(GTest REQUIRED)
find_package(tabulate REQUIRED)


include_directories("common/")
add_subdirectory("insertion_sort")
add_subdirectory("selection_sort")
add_subdirectory("merge_sort")


# Application which generates data and runs the sorting algorithms.
add_executable(GenSortingData "main_generate_data.cpp")

target_link_libraries(GenSortingData PUBLIC InsertionSortLib SelectionSortLib MergeSortLib tabulate::tabulate)


