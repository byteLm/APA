

add_executable(SelectionSortUnitTest "unittests_selection_sort.cpp")
target_link_libraries(SelectionSortUnitTest GTest::GTest GTest::Main SelectionSortLib)
