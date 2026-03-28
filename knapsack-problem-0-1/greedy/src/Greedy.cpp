
#include <vector>
#include <algorithm>

#include "Greedy.h"


#include <limits>
#include <algorithm>
#include <memory>

void GreedySolver::solve(int arrItensToStealAndTheirWeights[], int itensValues[], int sackSize, size_t arrItensToStealSize, size_t itensValuesSize, int* solution){

    if (arrItensToStealSize == 0 || arrItensToStealAndTheirWeights == nullptr || itensValues == nullptr || solution == nullptr) {
        return; 
    }

    if (arrItensToStealSize != itensValuesSize) {
        return; 
    }

    // Initialize solution with no itens yet
    for(size_t i = 0; i < arrItensToStealSize; i++){
        solution[i] = 0; 
    }

    // Transforming each item for struct; with this, we garantee in ordering we'll not lose which item we 
    // need to 'steal'.
    auto itens = std::make_unique<Item[]>(arrItensToStealSize);
    for(size_t idx = 0; idx < arrItensToStealSize; idx++){
        itens[idx].itemId = idx;
        itens[idx].weight = arrItensToStealAndTheirWeights[idx];
        itens[idx].value = itensValues[idx];
        
        if (arrItensToStealAndTheirWeights[idx] == 0) {
            if (itensValues[idx] > 0) {
                itens[idx].valuePerWeight = std::numeric_limits<float>::infinity();
            } else {
                itens[idx].valuePerWeight = 0.0f;
            }
        } else {
            itens[idx].valuePerWeight = (float)itensValues[idx] / arrItensToStealAndTheirWeights[idx]; 
        }
    }

    // ordering using criteria
    std::sort(itens.get(), itens.get() + arrItensToStealSize, [](const Item& a, const Item& b) { // std::sort is ~O(nlogn)
        return a.valuePerWeight > b.valuePerWeight; 
    }); 

    int actualSackWeight = 0;

    for(size_t i = 0; i < arrItensToStealSize; i++){
        if(itens[i].weight < 0) continue; 

        if(actualSackWeight + itens[i].weight <= sackSize){
            actualSackWeight += itens[i].weight;
            solution[itens[i].itemId] = 1; 
        }
    }
}
