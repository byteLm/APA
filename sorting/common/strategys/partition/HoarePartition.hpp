#ifndef HOAREPARTITION_H
#define HOAREPARTITION_H

#include "IPartitionStrategy.h"

/// @brief Implements the Hoare partition scheme for quicksort. 

class HoarePartition : public IPartitionStrategy {
public:
    std::pair<int,int> partition(int arr[], int idxStart, int idxEnd) override {

        int pivot = arr[idxStart];
        int i = idxStart - 1;
        int j = idxEnd + 1;

       while (true)
       {
            do {
                i++;
            } while (arr[i] < pivot);

            do {
                j--;
            } while (arr[j] > pivot);

            if (i >= j)
                return {j, j+1}; // implemented using pair to be more flexible to strategy pattern (Hoare and Lomuto have different return types)

            utils::swap(arr, i, j);
        }
       
    }
};

#endif // HOAREPARTITION_H