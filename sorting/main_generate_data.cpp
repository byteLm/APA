
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <chrono>
#include <memory>
#include <functional>

#include "InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std::chrono;

using Clock = std::chrono::steady_clock;

template <typename SortFunc>
long long measureSingleSort(SortFunc sortFunc, int* arr, int size) {
    auto start = Clock::now();
    sortFunc(arr, size);
    auto end = Clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

void runBenchmark(std::string filename, std::function<std::unique_ptr<int[]>(int)> generator) {
   
    const int NUM_RUNS = 5; // for each arr_size, we'll run this many times and take the average to get a more stable measurement
    const size_t MAX_ARRAY_SIZE = 5000; 

    InsertionSort insSort;
    SelectionSort selectSort;
    MergeSort mergeSort;
    QuickSort quickSort;
   
    std::ofstream file(filename);    
    file << "size,insertion_ns_avg_" << NUM_RUNS << ",selection_ns_avg_" << NUM_RUNS << ",merge_ns_avg_" << NUM_RUNS << ",quick_ns_avg_" << NUM_RUNS << "\n";

    std::cout << "Iniciando: " << filename << "..." << std::endl;

    // i read somewhere that the first few runs of a benchmark can be slower due to CPU optimizations and caching. 
    // So here we run a quick sort before starting the actual benchmark to "warm up" the CPU.
    auto warmUpArr = generator(1000);
    insSort.sort(warmUpArr.get(), 1000);

    for (int i = 1; i <= MAX_ARRAY_SIZE; i++) {
        int size = i;
        
        try {
            auto baseArr = generator(size);
            if (!baseArr) throw std::runtime_error("Erro ao gerar array");

            long long totalIns = 0;
            long long totalSelec = 0;
            long long totalMerge = 0;
            long long totalQuick = 0;

            for (int r = 0; r < NUM_RUNS; r++) {
                // Insertion Sort
                auto copyIns = utils::cloneArray(baseArr.get(), size);
                totalIns += measureSingleSort([&](int* a, int s){ insSort.sort(a, s); }, copyIns.get(), size);

                // Selection Sort
                auto copySelect = utils::cloneArray(baseArr.get(), size);
                totalSelec += measureSingleSort([&](int* a, int s){ selectSort.sort(a, s); }, copySelect.get(), size);

                // Merge Sort
                auto copyMerge = utils::cloneArray(baseArr.get(), size);
                totalMerge += measureSingleSort([&](int* a, int s){ mergeSort.sort(a, s); }, copyMerge.get(), size);

                // Quick Sort
                auto copyQuick = utils::cloneArray(baseArr.get(), size);
                totalQuick += measureSingleSort([&](int* a, int s){ quickSort.sort(a, s); }, copyQuick.get(), size);
            }

            // Calculate averages
            long long avgIns = totalIns / NUM_RUNS;
            long long avgSelec = totalSelec / NUM_RUNS;
            long long avgMerge = totalMerge / NUM_RUNS;
            long long avgQuick = totalQuick / NUM_RUNS;

            file << size << "," << avgIns << "," << avgSelec << "," << avgMerge << "," << avgQuick << "\n";

            if (i % 500 == 0) {
                std::cout << "  Processado: " << i << "/" << MAX_ARRAY_SIZE << std::endl;
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

    runBenchmark("bench_random.csv", [=](int s) { 
        return utils::generateRandomArray(s);
    });
    
    runBenchmark("bench_repeated.csv", [=](int s) { 
        return utils::generateRandomArrayWithRepeatedValues(s); 
    });
    
    runBenchmark("bench_sorted.csv", [=](int s) { 
        return utils::generateSortedArray(s); 
    });
    
    runBenchmark("bench_reverse.csv", [=](int s) { 
        return utils::generateReverseSortedArray(s);
    });

    return 0;
}