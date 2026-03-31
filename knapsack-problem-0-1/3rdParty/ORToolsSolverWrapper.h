#pragma once

#include <vector>
#include <numeric>
#include "ortools/algorithms/knapsack_solver.h"

class ORToolsSolver {
public:
    void solve(int arrItensToStealAndTheirWeights[], int itensValues[], int sackSize, 
               size_t arrItensToStealSize, size_t itensValuesSize, int* solution) {
        
        using namespace operations_research;

        // O OR-Tools permite escolher o backend. 
        // KNAPSACK_MULTIDIMENSION_BRANCH_AND_BOUND_SOLVER é o solver exato padrão e ultra-rápido.
        KnapsackSolver solver(KnapsackSolver::KNAPSACK_MULTIDIMENSION_BRANCH_AND_BOUND_SOLVER,
                              "Mochila_Google_ORTools");

        std::vector<int64_t> values(itensValues, itensValues + itensValuesSize);
        
        std::vector<std::vector<int64_t>> weights(1, std::vector<int64_t>(arrItensToStealAndTheirWeights, arrItensToStealAndTheirWeights + arrItensToStealSize));
        
        std::vector<int64_t> capacities = { static_cast<int64_t>(sackSize) };

        solver.Init(values, weights, capacities);

        solver.Solve();

        for (size_t i = 0; i < arrItensToStealSize; ++i) {
            solution[i] = solver.BestSolutionContains(i) ? 1 : 0;
        }
    }
};