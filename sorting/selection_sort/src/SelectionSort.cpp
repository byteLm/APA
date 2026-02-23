#include "SelectionSort.h"

/// @brief Sorts an array using the selection sort algorithm. That implementaion is based on pseudocode given in class.
/// @param A The array to be sorted.
/// @param n The size of the array.
void SelectionSort::sort(int A[], int n){
    if(n <= 1) return; // already sorted

    for(size_t i = 0; i<= n-2; i++){
        size_t i_min = i;
        for(size_t j = i+1; j <= n-1; j++){
            if(A[j] < A[i_min])
                i_min = j;
        }
        if(A[i] != A[i_min]){
            utils::swap(A, i, i_min);
        }
    }
}

