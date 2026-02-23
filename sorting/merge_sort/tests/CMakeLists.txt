

add_executable(MergeSortUnitTest "unittests_merge_sort.cpp")
target_link_libraries(MergeSortUnitTest GTest::GTest GTest::Main MergeSortLib)
