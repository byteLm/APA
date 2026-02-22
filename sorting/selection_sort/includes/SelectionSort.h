#include "interfaces.h"

class SelectionSort : public ISortingAlgorithm {
    public:
        void sort(int arr[], int size) override;
    private:
        static void exchange(int arr[], size_t idxA, size_t idxB);
};