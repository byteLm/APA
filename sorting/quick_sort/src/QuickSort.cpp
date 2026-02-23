#include "QuickSort.h"
#include <climits>

/// @brief Sorts an array using the quick sort algorithm. That implementaion is based on pseudocode given in class.
/// @param A The array to be sorted.
/// @param n The size of the array.
void QuickSort::sort(int A[], int n){
    if(n <= 1) return; // already sorted
    
    quickSort(A, 0, n-1);
    
}

/// @brief Sorts a portion of an array using the quick sort algorithm. This function is called recursively to sort the left and right partitions of the array.
/// @param A The array to be sorted.
/// @param l The starting index of the portion of the array to be sorted.
/// @param r The ending index of the portion of the array to be sorted.
void QuickSort::quickSort(int A[], int l, int r){
    if (l < r) {
        std::pair<int, int> limites = this->partitioner->partition(A, l, r);
        quickSort(A, l, limites.first);
        quickSort(A, limites.second, r);
    }
}
