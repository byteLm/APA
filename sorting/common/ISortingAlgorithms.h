
#ifndef ISORTINGALGORITHMS_H
#define ISORTINGALGORITHMS_H

#include <cstddef>
#include <iostream>
#include "utils.hpp"

/// @brief Interface for sorting algorithms.
class ISortingAlgorithm {
    public:
        virtual void sort(int arr[], int size) = 0;
};


#endif // ISORTINGALGORITHMS_H
