#include <gtest/gtest.h>
#include <random>
#include "Greedy.h"
#include "utils.hpp"

// Corrigido o nome de Greedyest para GreedyTest para seguir o padrão de nomenclatura
class GreedyTest : public ::testing::Test {
protected:
    void SetUp() override {
        this->solver = GreedySolver();
    }

    void TearDown() override {
    }

    GreedySolver solver;
};

TEST_F(GreedyTest, SingleElementMustFit) {
    int weights[] = {10};      
    int values[] = {100};      
    int sackSize = 15;         
    size_t size = 1;           
    int solution[] = {0};      

    this->solver.solve(weights, values, sackSize, size, size, solution);
    
    EXPECT_EQ(solution[0], 1) << "O único item deveria ter sido colocado na mochila, já que cabe.";
}

TEST_F(GreedyTest, MultipleItems_GreedyChoice) {
    // Razões: Item 0 = 6.0, Item 1 = 5.0, Item 2 = 4.0
    // O algoritmo VAI escolher na ordem: 0, depois 1, depois 2.
    int weights[] = {10, 20, 30};
    int values[]  = {60, 100, 120};
    int sackSize  = 50; 
    size_t size = 3;
    int solution[] = {0, 0, 0};

    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 1) << "Deveria pegar o item 0 (maior razão).";
    EXPECT_EQ(solution[1], 1) << "Deveria pegar o item 1 (segunda maior razão).";
    EXPECT_EQ(solution[2], 0) << "Não deveria ter espaço para o item 2.";
}

// ==========================================
// 2. MELHOR CASO
// ==========================================

TEST_F(GreedyTest, AllItemsFit) {
    // Capacidade da mochila é muito maior que o peso de todos os itens juntos
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

// ==========================================
// 3. CASOS ABSURDOS / EXTREMOS
// ==========================================

TEST_F(GreedyTest, ZeroCapacitySack) {
    // A mochila não aguenta peso nenhum
    int weights[] = {10, 20};
    int values[]  = {100, 200};
    int sackSize  = 0; 
    size_t size = 2;
    int solution[] = {1, 1}; // Inicializado com 1 de propósito para ver se o algoritmo zera

    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 0);
    EXPECT_EQ(solution[1], 0) << "Nenhum item deve ser inserido em uma mochila de capacidade 0.";
}

TEST_F(GreedyTest, AllItemsTooHeavy) {
    // A mochila tem capacidade, mas todos os itens são pesados demais
    int weights[] = {50, 60};
    int values[]  = {100, 200};
    int sackSize  = 20; 
    size_t size = 2;
    int solution[] = {0, 0};

    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 0);
    EXPECT_EQ(solution[1], 0) << "Nenhum item deve ser inserido pois todos excedem o limite.";
}

TEST_F(GreedyTest, EmptyArrays) {
    int sackSize  = 50; 
    size_t size = 0;

    EXPECT_NO_THROW({
        this->solver.solve(nullptr, nullptr, sackSize, size, size, nullptr);
    }) << "O algoritmo não deve quebrar ao tentar processar 0 itens.";
}


TEST_F(GreedyTest, GreedySuboptimalTrap) {
    // Esse teste é específico para validar que o algoritmo é guloso.
    // Se ele é guloso, ele vai olhar tão somente para as razões de forma 'míope', não globalmente
    // Assim, ele irá adicionar o elemento 0 (que tem maior razão), mas que não é a melhor solução
    // Que neste caso seria, olhando globalmente, [0, 1, 1].

    int weights[] = {30, 25, 25};
    int values[]  = {60, 45, 45};
    int sackSize  = 50; 
    size_t size = 3;
    int solution[] = {0, 0, 0};

    this->solver.solve(weights, values, sackSize, size, size, solution);

    EXPECT_EQ(solution[0], 1) << "Guloso DEVE cair na armadilha e pegar o item de maior razão primeiro.";
    EXPECT_EQ(solution[1], 0);
    EXPECT_EQ(solution[2], 0) << "O guloso não terá espaço para os outros itens após pegar o primeiro.";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}