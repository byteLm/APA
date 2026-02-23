#include <gtest/gtest.h>
#include <random>
#include "QuickSort.h"
#include "utils.hpp"

class QuickSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        this->quickSort = QuickSort();
    }

    void TearDown() override {
    }

    QuickSort quickSort;
};

TEST_F(QuickSortTest, EmptyArray) {

    int arr[] = {};
    int size = 0;
    
    try
    {
        this->quickSort.sort(arr, size);
    }
    catch(const std::exception& e)
    {
        FAIL() << "Sorting an empty array should not throw an exception.";
    }
    
}

TEST_F(QuickSortTest, SingleElement) {
    int arr[] = {100};
    int size = 1;
    
    try
    {
        this->quickSort.sort(arr, size);
    }
    catch(const std::exception& e)
    {
        FAIL() << "Sorting a single element array should not throw an exception.";
    }
    
    EXPECT_EQ(arr[0], 100) << "The single element should remain unchanged.";
}

// Requested cases
TEST_F(QuickSortTest, RandomArray) {

    int n = 10; // arr size
    std::unique_ptr<int[]> arr = utils::generateRandomArray(n);

    std::cout << "Original array: ";
    utils::printArray(arr.get(), n);
    
    // Sort the array
    this->quickSort.sort(arr.get(), n);

    std::cout << "\nSorted array: ";
    utils::printArray(arr.get(), n);

    // Verify it's sorted
    for (int i = 0; i < n - 1; i++) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}

TEST_F(QuickSortTest, LotOfNonUniqueArray) {
    int n = 10; // arr size
    int minValue = 0;
    int maxValue = 100;
    float repetitionChance = 0.85;

    std::unique_ptr<int[]> arr = utils::generateRandomArrayWithRepeatedValues(n, minValue, maxValue, repetitionChance);

    std::cout << "Original array: ";
    utils::printArray(arr.get(), n);
    
    // Sort the array
    this->quickSort.sort(arr.get(), n);

    std::cout << "\nSorted array: ";
    utils::printArray(arr.get(), n);

    // Verify it's sorted
    for (int i = 0; i < n - 1; i++) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}

TEST_F(QuickSortTest, SortedArray) {
    int n = 10; // arr size
    std::unique_ptr<int[]> arr = utils::generateSortedArray(n);

    std::cout << "Original array: ";
    utils::printArray(arr.get(), n);
    
    // Sort the array
    this->quickSort.sort(arr.get(), n);

    std::cout << "\nSorted array: ";
    utils::printArray(arr.get(), n);

    // Verify it's sorted
    for (int i = 0; i < n - 1; i++) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}

TEST_F(QuickSortTest, InverseSortedArray) {
    int n = 10; // arr size
    std::unique_ptr<int[]> arr = utils::generateReverseSortedArray(n);

    std::cout << "Original array: ";
    utils::printArray(arr.get(), n);
    
    // Sort the array
    this->quickSort.sort(arr.get(), n);

    std::cout << "\nSorted array: ";
    utils::printArray(arr.get(), n);

    // Verify it's sorted
    for (int i = 0; i < n - 1; i++) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}