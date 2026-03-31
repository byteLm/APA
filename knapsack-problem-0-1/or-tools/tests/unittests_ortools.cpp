#include <gtest/gtest.h>
#include <vector>
#include <random>

#include "Greedy.h"
#include "BruteForce.h"
#include "DPSolver.h"
#include "ORToolsSolverWrapper.h"

class KnapsackComparisonTest : public ::testing::Test {
protected:
    GreedySolver greedy;
    BruteForceSolver bruteForce;
    DPSolver dp;
    ORToolsSolver ort;

    int calculateTotalValue(const int* values, const int* solution, int size) {
        int total = 0;
        for (int i = 0; i < size; ++i) {
            if (solution[i] == 1) {
                total += values[i];
            }
        }
        return total;
    }
};

// Verifica se DP e BruteForce chegam na mesma resposta ótima do OR-Tools, 
// enquanto o Guloso falha ao escolher o item de maior densidade (valor/peso).
TEST_F(KnapsackComparisonTest, OptimalSolversBeatGreedyInTrapCase) {
    // Armadilha:
    // Item 0: ratio = 60/30 = 2.0 (Guloso vai pegar este)
    // Item 1: ratio = 45/25 = 1.8
    // Item 2: ratio = 45/25 = 1.8
    // Ótimo: Pegar Itens 1 e 2 (Peso=50, Valor=90)
    // Guloso: Pega Item 0 e não sobra espaço para mais nada (Peso=30, Valor=60)
    int weights[] = {30, 25, 25};
    int values[]  = {60, 45, 45};
    int sackSize  = 50; 
    size_t size = 3;

    int sol_ort[3] = {0};
    int sol_dp[3] = {0};
    int sol_bf[3] = {0};
    int sol_greedy[3] = {0};

    ort.solve(weights, values, sackSize, size, size, sol_ort);
    dp.solve(weights, values, sackSize, size, size, sol_dp);
    bruteForce.solve(weights, values, sackSize, size, size, sol_bf);
    greedy.solve(weights, values, sackSize, size, size, sol_greedy);

    int val_ort    = calculateTotalValue(values, sol_ort, size);
    int val_dp     = calculateTotalValue(values, sol_dp, size);
    int val_bf     = calculateTotalValue(values, sol_bf, size);
    int val_greedy = calculateTotalValue(values, sol_greedy, size);

    EXPECT_EQ(val_ort, 90) << "Baseline OR-Tools falhou ao encontrar o valor maximo.";
    
    EXPECT_EQ(val_dp, val_ort) << "A Programacao Dinamica deveria igualar o otimo do OR-Tools.";
    EXPECT_EQ(val_bf, val_ort) << "A Forca Bruta deveria igualar o otimo do OR-Tools.";
    
    EXPECT_LT(val_greedy, val_ort) << "O Guloso deveria ter encontrado um valor INFERIOR ao otimo do OR-Tools neste cenario.";
    EXPECT_EQ(val_greedy, 60) << "O Guloso caiu perfeitamente na armadilha e estagnou em 60 de valor.";
}

// Verifica se em uma instância aleatória de tamanho viável para força bruta, 
// o DP e a Força Bruta mantêm a consistência com o OR-Tools.
TEST_F(KnapsackComparisonTest, ExactSolversAlwaysMatchORTools) {
    const int num_items = 15;
    const int sackSize = 100;
    
    std::vector<int> weights(num_items);
    std::vector<int> values(num_items);
    
    std::mt19937 gen(42); // Seed fixa para reprodutibilidade no teste
    std::uniform_int_distribution<> weight_dist(10, 50);
    std::uniform_int_distribution<> value_dist(10, 100);

    for(int i = 0; i < num_items; i++) {
        weights[i] = weight_dist(gen);
        values[i] = value_dist(gen);
    }

    std::vector<int> sol_ort(num_items, 0);
    std::vector<int> sol_dp(num_items, 0);
    std::vector<int> sol_bf(num_items, 0);
    std::vector<int> sol_greedy(num_items, 0);

    ort.solve(weights.data(), values.data(), sackSize, num_items, num_items, sol_ort.data());
    dp.solve(weights.data(), values.data(), sackSize, num_items, num_items, sol_dp.data());
    bruteForce.solve(weights.data(), values.data(), sackSize, num_items, num_items, sol_bf.data());
    greedy.solve(weights.data(), values.data(), sackSize, num_items, num_items, sol_greedy.data());

    int val_ort = calculateTotalValue(values.data(), sol_ort.data(), num_items);
    int val_dp = calculateTotalValue(values.data(), sol_dp.data(), num_items);
    int val_bf = calculateTotalValue(values.data(), sol_bf.data(), num_items);
    int val_greedy = calculateTotalValue(values.data(), sol_greedy.data(), num_items);

    EXPECT_EQ(val_dp, val_ort) << "O DP divergiu do OR-Tools em um cenario aleatorio.";
    EXPECT_EQ(val_bf, val_ort) << "A Forca Bruta divergiu do OR-Tools em um cenario aleatorio.";
    
    EXPECT_LE(val_greedy, val_ort) << "Erro teorico: Um algoritmo guloso nunca pode superar a solucao exata.";
}

// Garante que não é apenas o valor ótimo que bate, mas que a solução binária gerada é válida 
// (os itens selecionados não ultrapassam a capacidade da mochila).
TEST_F(KnapsackComparisonTest, OutputArraysRespectWeightCapacity) {
    int weights[] = {12, 15, 20, 25};
    int values[]  = {20, 30, 40, 50};
    int sackSize  = 35;
    size_t size = 4;

    int sol_ort[4] = {0};
    int sol_dp[4] = {0};

    ort.solve(weights, values, sackSize, size, size, sol_ort);
    dp.solve(weights, values, sackSize, size, size, sol_dp);

    int totalWeightOrt = 0;
    int totalWeightDp = 0;

    for (size_t i = 0; i < size; i++) {
        if (sol_ort[i] == 1) totalWeightOrt += weights[i];
        if (sol_dp[i] == 1) totalWeightDp += weights[i];
    }

    EXPECT_LE(totalWeightOrt, sackSize) << "OR-Tools gerou uma solucao com sobrepeso!";
    EXPECT_LE(totalWeightDp, sackSize) << "DP gerou uma solucao com sobrepeso!";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}