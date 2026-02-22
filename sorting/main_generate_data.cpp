#include "InsertionSort.h"
#include "SelectionSort.h"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <chrono>
#include <memory>
#include <functional>

using namespace std::chrono;

// That helps to pass sorting functions as parameters in the benchmark runner
using SortFunction = std::function<void(int*, int)>;

long long measureSort(SortFunction sortFunc, int* arr, int size) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, size);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

void runBenchmark(std::string filename, std::function<std::unique_ptr<int[]>(int)> generator) {
    
    // csv header
    std::ofstream file(filename);    
    file << "size,insertion_us,selection_us\n";

    // used sorting algorithms
    InsertionSort insSort;
    SelectionSort selectSort;

    // benchmark loop
    std::cout << "Iniciando: " << filename << "..." << std::endl;
    size_t max_array_size = 5000; 
    for (int i = 1; i <= max_array_size; i++) {
        int size = i;
        
        try {
            auto baseArr = generator(size);
            if (!baseArr) throw std::runtime_error("Erro ao gerar array");

            // insertion sort
            auto copyIns = utils::cloneArray(baseArr.get(), size);
            long long tIns = measureSort([&](int* a, int s){ insSort.sort(a, s); }, copyIns.get(), size);

            // selection sort
            auto copySelect = utils::cloneArray(baseArr.get(), size);
            long long tSelec = measureSort([&](int* a, int s){ selectSort.sort(a, s); }, copySelect.get(), size);

            file << size << "," << tIns << ',' << tSelec << "\n";

            if (i % 500 == 0) {
                std::cout << "  Processado: " << i << "/5000" << std::endl;
                file.flush(); 
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro no tamanho " << i << ": " << e.what() << std::endl;
            break; 
        }
    }

    file.close();
    std::cout << "Salvo com sucesso: " << filename << "\n" << std::endl;
}

int main() {
    runBenchmark("bench_random.csv", [](int size) { return utils::generateRandomArray(size); });
    runBenchmark("bench_repeated.csv", [](int size) { return utils::generateRandomArrayWithRepeatedValues(size); });
    runBenchmark("bench_sorted.csv", [](int size) { return utils::generateSortedArray(size); });
    runBenchmark("bench_reverse.csv", [](int size) { return utils::generateReverseSortedArray(size); });

    return 0;
}