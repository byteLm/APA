
#ifndef  IKNAPSACKSOLVER_H
#define  IKNAPSACKSOLVER_H
#include <cstddef>
#include <iostream>

/// @brief Interface for knap-sack-problem 0-1 solver
class IKnapSackSolver{
    public:
    
        /// @brief Get the best solution for the knap-sack-problem 0-1.
        /// @param arrItensToStealAndTheirWeights Array with the itens we can steal and their corresponding weights. For example: [12, 1, 2, 3, 4] represents that we have item 0 with weight 12, item 1 with weight 1, item 2 with weight 2, and so on.
        /// @param itensValues Array with the values of each item.
        /// @param sackSize The maximum weight the knapsack can hold.
        /// @param arrItensToStealSize The size of the arrItensToStealAndTheirWeights array.
        /// @param itensValuesSize The size of the itensValues array.
        /// @param solution Pointer to an array where the solution will be stored, its size should be equal to the number of items (size_itens). The solution will be represented as a binary array, where 1 means the item is included in the knapsack and 0 means it is not included.
        virtual void solve(int arrItensToStealAndTheirWeights[], int itensValues[], int sackSize, size_t arrItensToStealSize, size_t itensValuesSize, int* solution) = 0;
};



#endif // IKNAPSACKSOLVER_H
