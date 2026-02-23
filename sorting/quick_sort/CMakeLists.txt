

include_directories("includes/") 

add_library(QuickSortLib "src/QuickSort.cpp")
target_include_directories(QuickSortLib PUBLIC "includes/") 

target_include_directories(QuickSortLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(QuickSortLib PUBLIC cxx_std_17)

add_subdirectory("tests/")