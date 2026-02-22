#if !defined(INTERFACES_SORTING)
#define INTERFACES_SORTING
#include <cstddef>
#include <iostream>

/// @brief Interface for sorting algorithms.
class ISortingAlgorithm {
    public:
        virtual void sort(int arr[], int size) = 0;
};

#endif // INTERFACES_SORTING
