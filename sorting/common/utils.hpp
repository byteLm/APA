

#ifndef APA_UTILS_HPP
#define APA_UTILS_HPP
#include <iostream>
#include <memory>
#include <random>
#include <algorithm>

/// Utils functions
namespace utils {

    /// @brief Generates a random array of integers. The size of the array, the range of values, and the seed for randomness can be specified.
    /// @param size The size of the array to generate. Default is 10.
    /// @param minValue The minimum value for the random integers. Default is 0. 
    /// @param maxValue  The maximum value for the random integers. Default is 999.
    /// @param seed The seed for the random number generator. Default is 42.
    /// @return A unique_ptr to an array of random integers.
    std::unique_ptr<int[]> generateRandomArray(int size = 10, int minValue = 0, int maxValue = 999, int seed = 42) {
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dis(minValue, maxValue);
        
        auto arr = std::make_unique<int[]>(size);
        for (int i = 0; i < size; i++) {
            arr[i] = dis(gen);
        }
        
        return arr;
    }

    /// @brief Generates a random array of integers with a certain chance of repeated values. The size of the array, the range of values, the repetition chance, and the seed for randomness can be specified.
    /// @param size The size of the array to generate. Default is 10.
    /// @param minValue The minimum value for the random integers. Default is 0.
    /// @param maxValue The maximum value for the random integers. Default is 999.
    /// @param repetitionChance The chance that a value will be repeated in the array. It should be between 0 and 1. Default is 0.3 (30% chance of repetition).
    /// @param seed The seed for the random number generator. Default is 42.
    /// @return A unique_ptr to an array of random integers with repeated values.
    std::unique_ptr<int[]> generateRandomArrayWithRepeatedValues(int size = 10, int minValue = 0, int maxValue = 999, float repetitionChance = 0.3, int seed = 42) {
    
        // random generator
        std::mt19937 gen(seed);

        // Pool size is determined by the repetition chance. The higher the repetition chance, the smaller the pool, and thus more repetitions in the final array.
        int poolSize = static_cast<int>(size * repetitionChance);
        if (poolSize < 1) poolSize = 1; 

        std::uniform_int_distribution<> randomValues(minValue, maxValue);

        // Generate a pool of possible values to be appended in the final array.
        auto possiblePoolValues = std::make_unique<int[]>(poolSize);
        for (int i = 0; i < poolSize; i++) {
            possiblePoolValues[i] = randomValues(gen);
        }

        // Now we generate the final array by randomly picking values from the pool.
        std::uniform_int_distribution<> dis(0, poolSize - 1);

        auto arr = std::make_unique<int[]>(size);
        for (int i = 0; i < size; i++) {
            arr[i] = possiblePoolValues[dis(gen)];
        }
        return arr;
    }


    /// @brief Generates a sorted array of integers. The size of the array, the range of values, and the seed for randomness can be specified. The generated array will be sorted in ascending order.
    /// @param size The size of the array to generate. Default is 10.
    /// @param minValue The minimum value for the random integers. Default is 0.
    /// @param maxValue  The maximum value for the random integers. Default is 999.
    /// @param seed The seed for the random number generator. Default is 42.
    /// @return A unique_ptr to a sorted array of random integers.
    std::unique_ptr<int[]> generateSortedArray(int size = 10, int minValue = 0, int maxValue = 999, int seed = 42) {
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dis(minValue, maxValue);
        auto arr = std::make_unique<int[]>(size);
        for (int i = 0; i < size; i++) {
            arr[i] = dis(gen);
        }
        std::sort(arr.get(), arr.get() + size);
        return arr; 
    }

    /// @brief  Generates a reverse sorted array of integers. The size of the array, the range of values, and the seed for randomness can be specified. The generated array will be sorted in descending order.
    /// @param size The size of the array to generate. Default is 10.
    /// @param minValue  The minimum value for the random integers. Default is 0.
    /// @param maxValue  The maximum value for the random integers. Default is 999.
    /// @param seed  The seed for the random number generator. Default is 42.
    /// @return A unique_ptr to a reverse sorted array of random integers.
    std::unique_ptr<int[]> generateReverseSortedArray(int size = 10, int minValue = 0, int maxValue = 999, int seed = 42) {
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dis(minValue, maxValue);
        auto arr = std::make_unique<int[]>(size);
        for (int i = 0; i < size; i++) {
            arr[i] = dis(gen);
        }
        std::sort(arr.get(), arr.get() + size, std::greater<int>());
        return arr; 
    }

    /// @brief It just print the array in a nice format. It is useful for debugging and testing purposes.
    /// @param arr The array to be printed.
    /// @param size The size of the array.
    void printArray(const int arr[], int size) {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }


}
#endif //APA_UTILS_HPP
