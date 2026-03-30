#include "IKnapSackSolver.h"
#include "Structures.h"

class DPSolver : public IKnapSackSolver {
    public:
        void solve(int arrItensToStealAndTheirWeights[], int itensValues[], int sackSize, size_t arrItensToStealSize, size_t itensValuesSize, int* solution) override;
};