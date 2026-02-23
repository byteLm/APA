#include "ISortingAlgorithms.h"
#include <cmath>
#include <vector>


class MergeSort : public ISortingAlgorithm {
    public:
        void sort(int arr[], int size) override;
    private:
        static void mergeSort(int arr[], size_t p, size_t r);
        static void merge(int arr[], size_t p, size_t q, size_t r);
};