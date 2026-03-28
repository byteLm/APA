#include "IKnapSackSolver.h"
#include "Structures.h"

/// @brief Greedy KnapSackSolver which use valuePerWeight as criteria.
class GreedySolver : public IKnapSackSolver {
    public:
        void solve(int arrItensToStealAndTheirWeights[], int itensValues[], int sackSize, size_t arrItensToStealSize, size_t itensValuesSize, int* solution) override;
};