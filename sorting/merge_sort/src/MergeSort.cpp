#include "MergeSort.h"
#include <climits>

/// @brief Sorts an array using the merge sort algorithm. That implementaion is based on pseudocode given in class.
/// @param A The array to be sorted.
/// @param n The size of the array.
void MergeSort::sort(int A[], int n){
    if(n <= 1) return; // already sorted

    mergeSort(A, 0, n-1);
    
}

void MergeSort::mergeSort(int arr[], size_t p, size_t r){
    
    if(p < r){
        size_t q = p + (r - p) / 2; // to avoid overflow, instead of (p + r) / 2
        mergeSort(arr, p, q);
        mergeSort(arr, q + 1, r);
        merge(arr, p, q, r);
    }

}
void MergeSort::merge(int arr[], size_t p, size_t q, size_t r){

    // this dinamically allocates the arrays L and R, its NOT supported in C++ to declare arrays with non-constant size, so we have to use dynamic allocation here.
    // size_t n_L = q - p + 1;
    // size_t n_R = r - q;
    // int L[n_L];
    // int R[n_R];

    std::vector<int> L = utils::copyArrayToVector(arr, p, q);
    std::vector<int> R = utils::copyArrayToVector(arr, q + 1, r);

    L.push_back(INT_MAX);
    R.push_back(INT_MAX);

    size_t i = 0;
    size_t j = 0;

    for(size_t k = p; k <= r; k++){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
    }
}


