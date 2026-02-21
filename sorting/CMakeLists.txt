cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler")
set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler")

project(SortAlgorithms)

set(CMAKE_CXX_STANDARD 17)


set(ROOT_DIR ${CMAKE_SOURCE_DIR})

include_directories("common/")

add_subdirectory("insertion_sort")
