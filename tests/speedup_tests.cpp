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
- find max (DONE)
- reduce left (add) (DONE)
- apply operation (*2) (DONE)
- orMap (DONE)

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

std::vector<int> generateRandomVec(const unsigned int n) {
    std::vector<int> vec;
    vec.reserve(n); // this reserves space to improve performance
    for (unsigned int i = 0; i < n; ++i) {
        vec.push_back((rand() % std::numeric_limits<int16_t>::max()) - 5000);
    }
    return vec;
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
    // smart pointer for memory management
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

    // parallel version
    const auto vecx_one = std::make_unique<palgox::palgox_vecx>(input_data_one);
    const auto start_par = std::chrono::high_resolution_clock::now();
    int result = vecx_one->findMax();
    const auto end_par = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_par = end_par - start_par;

    // Calculate speedup
    const double speedup = duration_seq.count() / duration_par.count();
    std::cout << "VecX findMax Speedup: " << speedup << "x" << std::endl;

    speedUpList.push_back(speedup);
}

void testReduceLeftVecx(const unsigned int n, std::vector<double>& speedUpList) {
    // custom rand between -20 and 20 values
    std::vector<int> vec;
    vec.reserve(n);
    for (unsigned int i = 0; i < n; ++i) {
        vec.push_back((rand() % 21) - 20);
    }

    // sequential version
    const auto start_seq = std::chrono::high_resolution_clock::now();
    int result = -10000;
    for (int i = 0; i < n; i++) {
        result = result + vec[i];
    }
    const auto end_seq = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_seq = end_seq - start_seq;

    // parallel version
    const auto vecx_one = std::make_unique<palgox::palgox_vecx>(vec);
    const auto start_par = std::chrono::high_resolution_clock::now();
    int result_par = vecx_one->reduceLeft(-10000, [](const int a, const int b){return a + b;});
    const auto end_par = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_par = end_par - start_par;

    // Calculate speedup
    const double speedup = duration_seq.count() / duration_par.count();
    std::cout << "VecX ReduceLeft Speedup: " << speedup << "x" << std::endl;

    speedUpList.push_back(speedup);
}

void testApplyOperationVecx(const unsigned int n, std::vector<double>& speedUpList) {
    std::vector<int> input_data_one = generateRandomVec(n);

    // parallel version
    const auto vecx_one = std::make_unique<palgox::palgox_vecx>(input_data_one);
    const auto start_par = std::chrono::high_resolution_clock::now();
    vecx_one->applyOperation([](const int num){return num * 2;});
    const auto end_par = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_par = end_par - start_par;

    // sequential version
    const auto start_seq = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        input_data_one[i] = input_data_one[i] * 2;
    }
    const auto end_seq = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_seq = end_seq - start_seq;

    // Calculate speedup
    const double speedup = duration_seq.count() / duration_par.count();
    std::cout << "VecX Apply Operation Speedup: " << speedup << "x" << std::endl;

    speedUpList.push_back(speedup);
}

void testOrMapVecx(const unsigned int n, std::vector<double>& speedUpList) {
    std::vector<int> input_data_one = generateRandomVec(n);

    // sequential version
    const auto start_seq = std::chrono::high_resolution_clock::now();
    bool ret = false;
    for (int i = 0; i < n; i++) {
        ret |= (input_data_one[i] < 4900);
    }
    const auto end_seq = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_seq = end_seq - start_seq;

    // parallel version
    const auto vecx_one = std::make_unique<palgox::palgox_vecx>(input_data_one);
    const auto start_par = std::chrono::high_resolution_clock::now();
    vecx_one->orMap([](const int num){return num < 4900;});
    const auto end_par = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration_par = end_par - start_par;

    // Calculate speedup
    const double speedup = duration_seq.count() / duration_par.count();
    std::cout << "VecX OrMap Speedup: " << speedup << "x" << std::endl;

    speedUpList.push_back(speedup);
}

int main() {
    constexpr unsigned int n = 10000000; // large input where n = 10 mil
    std::vector<double> speedUpVecxList;
    for (int i = 0; i < 10; i++) {
        // put testing method here
        testOrMapVecx(n, speedUpVecxList);
    }
    // testSearchVecx(n, speedUpVecxList);
    // testFindMaxVecx(n, speedUpVecxList);
    // testReduceLeftVecx(n, speedUpVecxList);
    // testApplyOperationVecx(n, speedUpVecxList);
    // testOrMapVecx(n, speedUpVecxList);

    // compute average speed up
    double average = 0;
    for (const double& speedUp : speedUpVecxList) {
        average += speedUp;
    }
    average /= speedUpVecxList.size();
    std::cout << "Average Vecx Speedup: " << average << "x" << std::endl;
    return 0;
}