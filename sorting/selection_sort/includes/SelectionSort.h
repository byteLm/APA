#include "interfaces.h"

class SelectionSort : public ISortingAlgorithm {
    public:
        void sort(int arr[], int size) override;
};