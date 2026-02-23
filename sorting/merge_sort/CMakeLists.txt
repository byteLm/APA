

include_directories("includes/") 
add_library(MergeSortLib "src/MergeSort.cpp")
target_include_directories(MergeSortLib PUBLIC "includes/") 

target_include_directories(MergeSortLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(MergeSortLib PUBLIC cxx_std_17)

add_subdirectory("tests/")