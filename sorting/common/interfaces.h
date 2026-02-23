#if !defined(INTERFACES_SORTING)
#define INTERFACES_SORTING
#include <cstddef>
#include <iostream>
#include "utils.hpp"

/// @brief Interface for sorting algorithms.
class ISortingAlgorithm {
    public:
        virtual void sort(int arr[], int size) = 0;
};

#endif // INTERFACES_SORTING
