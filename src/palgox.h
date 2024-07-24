#ifndef PALGOX_LIBRARY_H
#define PALGOX_LIBRARY_H

#include <utility>
#include <vector>
#include <exception>
#include <string>
#include <iostream>
#include <omp.h>
#include <thread>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <stack>
#include <cmath>
#include <random>
#include <unordered_set>

namespace palgox {
    class palgoxException final : public std::exception {
    private:
        std::string msg_;
    public:
        explicit palgoxException(std::string msg) : msg_(std::move(msg)) {}
        std::string what() { return this->msg_;}
    };

    class palgox_vecx {
    private:
        std::vector<int> m_data;
        int m_numElems;

        bool isSameSize(const palgox_vecx* other_vecx) const;

        void quickSortHelper(std::vector<int>& arr, int low, int high);

        static int partition(std::vector<int>& arr,int low,int high);

        void mergeSortHelper(std::vector<int>& arr, int begin, int end);

        static void merge(std::vector<int>& arr, int left, int mid, int right);

        static void findMinHelper(const std::vector<int>& data, int start, int end, int& min_elem);

        static void findMaxHelper(const std::vector<int>& data, int start, int end, int& max_elem);
    public:
        explicit palgox_vecx(const std::vector<int>& input_data);

        explicit palgox_vecx(int size, int (*operation)(int));

        bool isEqual(const palgox_vecx* other_vecx) const;

        [[nodiscard]] int getNumElems() const;

        [[nodiscard]] int getValue(int idx) const;

        void applyOperation(int (*operation)(int));

        void addVecx(const palgox_vecx* other_vecx);

        void subVecx(const palgox_vecx* other_vecx);

        [[nodiscard]] int search(int value) const;

        void quickSort();

        void mergeSort();

        palgox_vecx* filter(bool (*operation)(int)) const;

        bool andMap(bool (*operation)(int)) const;

        bool orMap(bool (*operation)(int)) const;

        int reduceLeft(int init, int (*operation)(int, int)) const;

        int reduceRight(int init, int (*operation)(int, int)) const;

        [[nodiscard]] int findMin() const;

        [[nodiscard]] int findMax() const;

        [[nodiscard]] palgox_vecx* prefixSum() const;

        [[nodiscard]] palgox_vecx* suffixSum() const;

    };

    class palgox_matx {
    private:
        std::vector<std::vector<int>> m_data;
        int m_numRow;
        int m_numCol;

        bool isSameShape(const palgox_matx* other_matx) const;

        void applyOperation(const palgox_matx* other_matx, int (*operation)(int, int));
    public:
        explicit palgox_matx(const std::vector<std::vector<int>>& input_data);

        bool isEqual(const palgox_matx* other_matx) const;

        void addMatx(const palgox_matx* other_matx);

        void subMatx(const palgox_matx* other_matx);

        [[nodiscard]] palgox_matx* getTranspose() const;

        palgox_matx* mulMatx(const palgox_matx* other_matx) const;

        [[nodiscard]] int getNumRows() const;

        [[nodiscard]] int getNumCols() const;

        [[nodiscard]] int getValue(int row, int col) const;

        bool andMap(bool (*operation)(int)) const;

        bool orMap(bool (*operation)(int)) const;

    };

    class palgox_graphx {
    private:
        std::unordered_map<int, std::unordered_set<int>> m_adjList;
        int m_numVertices;
        int m_numEdges;

        bool hasCycleHelper(int vertex, std::vector<bool>& visited, int parent);

    public:

        explicit palgox_graphx(int numVertices);

        void addEdge(int src_node, int dest_node);

        std::unordered_set<int> getNeighboringNodes(int node) const;

        int getNumVertices() const;

        bool isEqual(const palgox_graphx* other_graphx) const;

        bool hasCycle();
    };


    class palgox_mathx {
    public:

        static std::vector<int> computePowers(const std::vector<int>& bases, const std::vector<int>& exponents) {
            std::vector<int> results(bases.size());
#pragma omp parallel for
            for (int i = 0; i < bases.size(); ++i) {
                results[i] = static_cast<int>(std::pow(bases[i], exponents[i]));
            }
            return results;
        }

        static unsigned long long factorial(const unsigned int n) {
            if (n == 0 || n == 1) return 1;
            unsigned long long result = 1;
#pragma omp parallel for reduction(*:result)
            for (int i = 2; i <= n; ++i) {
                result *= i;
            }
            return result;
        }

        static std::vector<bool> generatePrimes(unsigned int n) {
            std::vector<bool> is_prime(n + 1, true);
            is_prime[0] = is_prime[1] = false;
            const int limit = static_cast<int>(std::sqrt(n));
#pragma omp parallel for schedule(dynamic)
            for (int i = 2; i <= limit; ++i) {
                if (is_prime[i]) {
                    for (int j = i * i; j <= n; j += i) {
                        is_prime[j] = false;
                    }
                }
            }
            return is_prime;
        }
    };
}

#endif //PALGOX_LIBRARY_H
