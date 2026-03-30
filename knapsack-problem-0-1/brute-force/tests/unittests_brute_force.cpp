#include <gtest/gtest.h>
#include <random>
#include "BruteForce.h"
#include "utils.hpp"

class BruteForceTest : public ::testing::Test {
protected:
    void SetUp() override {
        this->solver = BruteForceSolver();
    }

    void TearDown() override {
    }

    BruteForceSolver solver;
};


TEST_F(BruteForceTest, SingleElementMustFit) {
    int weights[] = {10};      
    int values[] = {100};      
    int sackSize = 15;         
    size_t size = 1;           
    int solution[] = {0};      

    this->solver.solve(weights, values, sackSize, size, size, solution);
    
    EXPECT_EQ(solution[0], 1) << "O único item deveria ter sido colocado na mochila, já que cabe.";
}

TEST_F(BruteForceTest, MultipleItems_OptimalChoice) {
    
    int weights[] = {10, 20, 30};
    int values[]  = {60, 100, 120};
    int sackSize  = 50; 
    size_t size = 3;
    int solution[] = {0, 0, 0};

    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 0) << "O item 0 não faz parte da solução ótima.";
    EXPECT_EQ(solution[1], 1) << "Deveria pegar o item 1 para maximizar o valor.";
    EXPECT_EQ(solution[2], 1) << "Deveria pegar o item 2 para maximizar o valor.";
}


TEST_F(BruteForceTest, AllItemsFit) {
    int weights[] = {5, 10, 15};
    int values[]  = {50, 60, 70};
    int sackSize  = 100;
    size_t size = 3;
    int solution[] = {0, 0, 0};

    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 1) << "Todos os itens devem estar na solução final.";
    EXPECT_EQ(solution[1], 1) << "Todos os itens devem estar na solução final.";
    EXPECT_EQ(solution[2], 1) << "Todos os itens devem estar na solução final.";
}

TEST_F(BruteForceTest, ZeroCapacitySack) {
    int weights[] = {10, 20};
    int values[]  = {100, 200};
    int sackSize  = 0; 
    size_t size = 2;
    int solution[] = {1, 1}; 
    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 0);
    EXPECT_EQ(solution[1], 0) << "Nenhum item deve ser inserido em uma mochila de capacidade 0.";
}

TEST_F(BruteForceTest, AllItemsTooHeavy) {
    int weights[] = {50, 60};
    int values[]  = {100, 200};
    int sackSize  = 20; 
    size_t size = 2;
    int solution[] = {0, 0};

    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 0);
    EXPECT_EQ(solution[1], 0) << "Nenhum item deve ser inserido pois todos excedem o limite.";
}

TEST_F(BruteForceTest, EmptyArrays) {
    int sackSize  = 50; 
    size_t size = 0;

    EXPECT_NO_THROW({
        this->solver.solve(nullptr, nullptr, sackSize, size, size, nullptr);
    }) << "O algoritmo não deve quebrar ao tentar processar 0 itens.";
}


TEST_F(BruteForceTest, BruteForceSuboptimalTrap) {
    // Esse teste é específico para validar que o algoritmo é exato (encontra o ótimo global).
    // O Guloso pegaria apenas o elemento 0 (que tem a maior razão).
    // A Força Bruta deve testar todas as ramificações e perceber que pegar os itens 1 e 2
    // gera um valor de 90, contrapondo os 60 do item 0.

    int weights[] = {30, 25, 25};
    int values[]  = {60, 45, 45};
    int sackSize  = 50; 
    size_t size = 3;
    int solution[] = {0, 0, 0};

    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 0) << "Força bruta NÃO irá cair na armadilha de pegar apenas o de maior razão.";
    EXPECT_EQ(solution[1], 1) << "Deve selecionar o item 1 para a solução ótima.";
    EXPECT_EQ(solution[2], 1) << "Deve selecionar o item 2 para a solução ótima.";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}