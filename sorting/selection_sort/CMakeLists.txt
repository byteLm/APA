

include_directories("includes/") 
add_library(SelectionSortLib "src/SelectionSort.cpp")
target_include_directories(SelectionSortLib PUBLIC "includes/") 

target_include_directories(SelectionSortLib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(SelectionSortLib PUBLIC cxx_std_17)

add_subdirectory("tests/")