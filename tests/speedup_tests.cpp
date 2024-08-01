#include <iostream>
#include <vector>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include "../src/palgox.h"

/*

// TESTING FUNCTIONS:

vec:
- search (DONE)
- find max
- filter
- apply operation
- sub vector

mat:
- add matrix
- get transpose
- multiply matrix

graph:
- has Cycle

math:
- factorial
- compute powers
*/

std::vector<int> generateRandomVec(unsigned int n) {
    std::vector<int> vec;
    vec.reserve(n); // this reserves space to improve performance
    for (unsigned int i = 0; i < n; ++i) {
        vec.push_back((rand() % std::numeric_limits<int16_t>::max()) - 5000);
    }
    return vec;
}

void testFindMaxVecx(const unsigned int n, std::vector<double>& speedUpList) {
    std::vector<int> input_data_one = generateRandomVec(n);

    // sequential version
    const auto start_seq = std::chrono::high_resolution_clock::now();
    int maxNum = -5001;
    for (int i = 0; i < n; i++) {
        maxNum = std::max(maxNum, input_data_one[i]);
    }
    const auto end_seq = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_seq = end_seq - start_seq;

    
}

void testSearchVecx(const unsigned int n, std::vector<double>& speedUpList) {
    std::vector<int> input_data_one = generateRandomVec(n);
    constexpr int value = std::numeric_limits<int16_t>::max() + 10000; // special value
    input_data_one[7000000] = value;

    // sequential version
    const auto start_seq = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        if (input_data_one[i] == value) break;
    }
    const auto end_seq = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_seq = end_seq - start_seq;
    // std::cout << "Sequential implementation took " << duration_seq.count() << " seconds." << std::endl;

    // parallel version
    const auto vecx_one = std::make_unique<palgox::palgox_vecx>(input_data_one);
    const auto start_par = std::chrono::high_resolution_clock::now();
    int result = vecx_one->search(value);
    const auto end_par = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_par = end_par - start_par;
    // std::cout << "Parallel implementation took " << duration_par.count() << " seconds." << std::endl;

    // Calculate speedup
    const double speedup = duration_seq.count() / duration_par.count();
    std::cout << "VecX Search Speedup: " << speedup << "x" << std::endl;

    speedUpList.push_back(speedup);
}

int main() {
    constexpr unsigned int n = 10000000; // large input where n = 10 mil
    std::vector<double> speedUpList;
    testSearchVecx(n, speedUpList);
    // smart pointer for memory management
    // std::vector<int> input_data_one = generateRandomVec(n);
    // std::vector<int> input_data_two = generateRandomVec(n);
    // auto vecx_one = std::make_unique<palgox::palgox_vecx>(input_data_one);
    // auto vecx_two = std::make_unique<palgox::palgox_vecx>(input_data_two);
    double average = 0;
    for (const double& speedUp : speedUpList) {
        average += speedUp;
    }
    average /= speedUpList.size();
    std::cout << "Average Speedup: " << average << "x" << std::endl;
    return 0;
}