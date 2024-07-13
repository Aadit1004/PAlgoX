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
#include <mutex>
#include <queue>
#include <stack>
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
        std::mutex mtx;

        bool hasCycleHelper(int vertex, std::vector<bool>& visited, int parent);

    public:

        explicit palgox_graphx(int numVertices);

        void addEdge(int src_node, int dest_node);

        std::unordered_set<int> getNeighboringNodes(int node) const;

        int getNumVertices() const;

        bool isEqual(const palgox_graphx* other_graphx) const;

        palgox_vecx* DFS(int startVertex);

        palgox_vecx* BFS(int startVertex);

        palgox_vecx* shortestPath(int startVertex, int targetVertex);

        bool hasCycle();

        palgox_vecx* topologicalSort();

        int getNumConnectedComponents(); // kosaraju algorithm?

    };

    // TODO: static class math utils
}

#endif //PALGOX_LIBRARY_H
