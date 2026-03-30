
#include <vector>
#include <algorithm>
#include <limits>
#include <memory>

#include "DPSolver.h"

void DPSolver::solve(int arrItensToStealAndTheirWeights[], int itensValues[], int sackSize, size_t arrItensToStealSize, size_t itensValuesSize, int* solution){

    if (arrItensToStealSize == 0 || arrItensToStealAndTheirWeights == nullptr || itensValues == nullptr || solution == nullptr) {
        return; 
    }
    if (arrItensToStealSize != itensValuesSize) {
        return; 
    }

    for(size_t i = 0; i < arrItensToStealSize; i++){
        solution[i] = 0; 
    }

    // matrix 4 map results
    std::vector<std::vector<int>> dp(arrItensToStealSize + 1, std::vector<int>(sackSize + 1, 0));

    // bottom-Up by each item and capacity
    for (size_t i = 1; i <= arrItensToStealSize; i++) {
        for (int w = 1; w <= sackSize; w++) {
            
            int currentWeight = arrItensToStealAndTheirWeights[i - 1]; 
            int currentValue = itensValues[i - 1];                     

            if (currentWeight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - currentWeight] + currentValue);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }


    // re-mapping final solution
    int w = sackSize;
    for (size_t i = arrItensToStealSize; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            solution[i - 1] = 1; 
            w -= arrItensToStealAndTheirWeights[i - 1]; 
        } else {
            solution[i - 1] = 0;
        }
    }
}