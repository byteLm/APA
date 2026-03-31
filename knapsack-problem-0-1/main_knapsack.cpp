#include <fstream>
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>

#include "utils.hpp" 
#include "Greedy.h"
#include "BruteForce.h" 
#include "DPSolver.h" 
#include "ORToolsSolverWrapper.h"

using namespace std::chrono;
using Clock = std::chrono::steady_clock;

struct ApsTestCase {
    int n;          // n itens
    int Q;          // sack size
    int minWeight;
    int maxWeight;
    int minValue;
    int maxValue;
};

template <typename SolveFunc>
long long measureSingleSolve(SolveFunc solveFunc) {
    auto start = Clock::now();
    solveFunc();
    auto end = Clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

void runAPSBenchmark(std::string filename) {
    
    const int MAX_BRUTE_FORCE_N = 35; 

    std::vector<ApsTestCase> testCases = {
        {10, 10, 1, 10, 1, 1000},  
        {15, 10, 1, 10, 1, 1000},  
        {20, 10, 1, 10, 1, 1000},  // REQUESTED
        {25, 20, 1, 20, 1, 1000},  
        {28, 20, 1, 20, 1, 1000},   
        {30, 20, 1, 20, 1, 1000},  
        {32, 20, 1, 20, 1, 1000},  // 2^32!!
        
        {33, 20, 1, 20, 1, 1000},  
        {34, 20, 1, 20, 1, 1000},  
        {35, 20, 1, 20, 1, 1000}, 
        
        {50, 30, 1, 30, 1, 1000},  // REQUESTED  
        {100, 30, 1, 30, 1, 1000}, // REQUESTED
        {200, 50, 1, 50, 1, 1000}, // REQUESTED
        {300, 50, 1, 50, 1, 1000}, 
        {500, 10, 1, 10, 1, 1000}, // REQUESTED
        {500, 100, 1, 100, 1, 1000}, // REQUESTED
        {750, 50, 1, 50, 1, 1000}, 
        {1000, 50, 1, 50, 1, 1000},// REQUESTED
        
        {2500, 100, 1, 100, 1, 1000}, 
        {5000, 100, 1, 100, 1, 1000}, 
        {10000, 100, 1, 100, 1, 1000},// REQUESTED
        {50000, 100, 1, 100, 1, 1000}, 
        {50000, 1000, 1, 100, 1, 1000}, // insane big Q to test n*q complexity
        {50000, 5000, 1, 100, 1, 1000}, // insane big Q to test n*q complexity
        
        {100000, 100, 1, 100, 1, 1000},
        {250000, 100, 1, 100, 1, 1000},
        {500000, 100, 1, 100, 1, 1000}, // REQUESTED
        {1000000, 100, 1, 100, 1, 1000}, // 1kk itens
        {5000000, 100, 1, 100, 1, 1000}  // 5kk itens
    };

    const int NUM_RUNS = 5; 

    GreedySolver greedy;
    BruteForceSolver bruteForce;
    DPSolver dp;
    ORToolsSolver ort;
    
    std::ofstream file(filename);    
    file << "n,Q,greedy_ns_avg" 
         << ",bruteforce_ns_avg" 
         << ",dp_ns_avg" 
         << ",ortools_ns_avg" 
         << "\n";

    std::cout << "Iniciando Benchmark da APS: " << filename << "..." << std::endl;

    for (const auto& test : testCases) {
        std::cout << "Processando n=" << test.n << ", Q=" << test.Q << "..." << std::flush;
        
        try {
            auto weights = utils::generateRandomArray(test.n, test.minWeight, test.maxWeight);
            auto values = utils::generateRandomArray(test.n, test.minValue, test.maxValue);
            auto solution = std::make_unique<int[]>(test.n);
            
            if (!weights || !values) throw std::runtime_error("Erro ao gerar arrays");

            long long totalGreedy = 0;
            long long totalBrute = 0;
            long long totalDP = 0;
            long long totalORTools = 0;

            for (int r = 0; r < NUM_RUNS; r++) {

                std::fill(solution.get(), solution.get() + test.n, 0);
                totalGreedy += measureSingleSolve([&]() { 
                    greedy.solve(weights.get(), values.get(), test.Q, test.n, test.n, solution.get()); 
                });

                if (test.n <= MAX_BRUTE_FORCE_N) {
                    std::fill(solution.get(), solution.get() + test.n, 0);
                    totalBrute += measureSingleSolve([&]() { 
                        bruteForce.solve(weights.get(), values.get(), test.Q, test.n, test.n, solution.get()); 
                    });
                } else {
                    totalBrute = -1; // 'aborted flag'
                }

                std::fill(solution.get(), solution.get() + test.n, 0);
                totalDP += measureSingleSolve([&]() { 
                    dp.solve(weights.get(), values.get(), test.Q, test.n, test.n, solution.get()); 
                });

                std::fill(solution.get(), solution.get() + test.n, 0);
                totalORTools += measureSingleSolve([&]() { 
                    ort.solve(weights.get(), values.get(), test.Q, test.n, test.n, solution.get()); 
                });
            }

            long long avgGreedy = totalGreedy / NUM_RUNS;
            long long avgBrute = (test.n <= MAX_BRUTE_FORCE_N) ? (totalBrute / NUM_RUNS) : -1;
            long long avgDP = totalDP / NUM_RUNS;
            long long avgORTools = totalORTools / NUM_RUNS;

            file << test.n << "," << test.Q << "," << avgGreedy 
                 << "," << avgBrute 
                 << "," << avgDP 
                 << "," << avgORTools
                 << "\n";
                 
            std::cout << " [OK]" << std::endl;

        } catch (const std::exception& e) {
            std::cerr << " [ERRO]: " << e.what() << std::endl;
        }
    }

    file.close();
    std::cout << "\nResultados salvos com sucesso em: " << filename << std::endl;
}

int main() {
    runAPSBenchmark("resultados_aps_mochila.csv");
    return 0;
}