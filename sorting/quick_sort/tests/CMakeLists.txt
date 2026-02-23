

add_executable(QuickSortUnitTest "unittests_quick_sort.cpp")
target_link_libraries(QuickSortUnitTest GTest::GTest GTest::Main QuickSortLib)
