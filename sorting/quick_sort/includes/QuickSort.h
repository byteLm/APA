
#include <cmath>
#include <vector>
#include <memory>

#include "ISortingAlgorithms.h"
#include "IPartitionStrategy.h"
#include "strategys/partition/HoarePartition.h"


class QuickSort : public ISortingAlgorithm {
    public:
        void sort(int arr[], int size) override;

    private:
        std::unique_ptr<IPartitionStrategy> partitioner = std::make_unique<HoarePartition>();
        void quickSort(int arr[], int l, int r);
};