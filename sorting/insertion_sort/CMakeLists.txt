

include_directories("includes/") # insertion_sort/includes/
add_executable(InsertionSortSampleAPP "main.cpp" "src/InsertionSort.cpp")

add_library(InsertionSortLib "src/InsertionSort.cpp")
target_include_directories(InsertionSortLib PUBLIC "includes/") 


add_subdirectory("tests/")