

include_directories("includes/") # insertion_sort/includes/
add_library(InsertionSortLib "src/InsertionSort.cpp")
target_include_directories(InsertionSortLib PUBLIC "includes/") 

target_include_directories(InsertionSortLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(InsertionSortLib PUBLIC cxx_std_17)

add_subdirectory("tests/")