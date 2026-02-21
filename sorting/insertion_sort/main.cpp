

#include <iostream>
#include "includes/InsertionSort.h"

using namespace std;

int main(){

    InsertionSort insertionSort;
    int arr[] = {12, 11, 13, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    insertionSort.sort(arr, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}