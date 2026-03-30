#include <limits>
#include <memory>
#include <functional>
#include "BruteForce.h"

void BruteForceSolver::solve(int arrItensToStealAndTheirWeights[], int itensValues[], int sackSize, size_t arrItensToStealSize, size_t itensValuesSize, int* solution){

    if (arrItensToStealSize == 0 || arrItensToStealAndTheirWeights == nullptr || itensValues == nullptr || solution == nullptr) {
        return; 
    }
    if (arrItensToStealSize != itensValuesSize) {
        return; 
    }

    int bestValue = -1;
    
    auto currentSolution = std::make_unique<int[]>(arrItensToStealSize);
    
    for(size_t i = 0; i < arrItensToStealSize; i++){
        solution[i] = 0; 
    }

    // test 2^n possibilities
    std::function<void(size_t, int, int)> explore = [&](size_t itemIndex, int currentWeight, int currentValue) {
        
        // end of item list (base leaf)
        if (itemIndex == arrItensToStealSize) {

            // if this timeline generated best solution 
            if (currentValue > bestValue) {
                bestValue = currentValue; 
                for (size_t i = 0; i < arrItensToStealSize; i++) {
                    solution[i] = currentSolution[i];
                }
            }
            return;
        }


        // first option: do not pick the item
        currentSolution[itemIndex] = 0;
        explore(itemIndex + 1, currentWeight, currentValue);

        // second option: get item if it fits in sack
        if (currentWeight + arrItensToStealAndTheirWeights[itemIndex] <= sackSize) {
            currentSolution[itemIndex] = 1;
            explore(itemIndex + 1, currentWeight + arrItensToStealAndTheirWeights[itemIndex], currentValue + itensValues[itemIndex]);
        }
    };

    // entrypoint
    explore(0, 0, 0);
}