
#ifndef IPARTITIONSTRATEGY_H
#define IPARTITIONSTRATEGY_H

#include <cstddef>
#include <iostream>
#include <utility> // std::pair
#include "utils.hpp"

/// @brief Interface for partition strategies used in quicksort.
class IPartitionStrategy {
public:
    virtual ~IPartitionStrategy() = default; 

    /// @brief Partitions a portion of an array and returns the indices that define the partitions. 
    /// @param arr The array to be partitioned.
    /// @param idxStart The starting index of the portion of the array to be partitioned.
    /// @param idxEnd The ending index of the portion of the array to be partitioned.
    /// @return A pair of integers representing the indices that define the partitions of the array after partitioning. The first integer is the index of the last element of the left partition,
    /// and the second integer is the index of the first element of the right partition.
    virtual std::pair<int, int> partition(int arr[], int idxStart, int idxEnd) = 0; 
};

#endif // IPARTITIONSTRATEGY_H