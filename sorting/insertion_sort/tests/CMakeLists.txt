

add_executable(InsertionSortUnitTest "unittests_insertion_sort.cpp")
target_link_libraries(InsertionSortUnitTest GTest::GTest GTest::Main InsertionSortLib)
