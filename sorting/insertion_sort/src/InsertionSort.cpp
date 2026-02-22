#include "InsertionSort.h"

/// @brief Sorts an array using the insertion sort algorithm. That implementaion is based on pseudocode given in class.
/// @param A The array to be sorted.
/// @param n The size of the array.
void InsertionSort::sort(int A[], int n){

    if(n <= 1) return; // already sorted

    int pivo = -1;
    int j = -1; // cant be size_t because j-1 sometime goes to -1 

    for(size_t i = 1; i <= n-1; i++){
        pivo = A[i];
        j = i - 1;

        while(j>= 0 && A[j] > pivo){
            A[j+1] = A[j];
            j = j-1;
        }
        A[j+1] = pivo;
    }
}