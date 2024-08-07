#include "palgox.h"

/*
 *
 *  PAlgoX_VecX implementations
 *
 */

// Constructor 1
palgox::palgox_vecx::palgox_vecx(const std::vector<int>& input_data) {
    if (input_data.empty()) throw palgoxException("Input data is empty");
    this->m_numElems = static_cast<int>(input_data.size());
    this->m_data = input_data;
}

// Constructor 2
palgox::palgox_vecx::palgox_vecx(const int size, int (*operation)(int)) {
    if (size <= 0) throw palgoxException("Input size must be positive");
    this->m_data.resize(size);
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        this->m_data[i] = operation(i);
    }
    this->m_numElems = size;
}

bool palgox::palgox_vecx::isSameSize(const palgox_vecx* other_vecx) const {
    return this->m_numElems == other_vecx->getNumElems();
}

bool palgox::palgox_vecx::isEqual(const palgox_vecx* other_vecx) const {
    if (!this->isSameSize(other_vecx)) return false;
    bool result = true;
#pragma omp parallel for
    for (int i = 0; i < this->m_data.size(); ++i) {
        if (!result) continue;  // check shared result
        if (this->m_data[i] != other_vecx->m_data[i]) {
#pragma omp critical
            {
                result = false;  // update result safely
            }
        }
    }
    return result;
}

int palgox::palgox_vecx::getNumElems() const {
    return this->m_numElems;
}

int palgox::palgox_vecx::getValue(const int idx) const {
    if (idx < 0 || idx > this->m_numElems - 1) {
        throw palgoxException("Invalid index parameter");
    }
    return this->m_data[idx];
}

void palgox::palgox_vecx::applyOperation(int (*operation)(int)) {
#pragma omp parallel for
    for (int i = 0; i < this->m_numElems; i++) {
        this->m_data[i] = operation(this->m_data[i]);
    }
}

void palgox::palgox_vecx::addVecx(const palgox_vecx* other_vecx) {
    if (!this->isSameSize(other_vecx)) {
        throw palgoxException("Different number of elements");
    }
#pragma omp parallel for
    for (int i = 0; i < this->m_numElems; i++) {
        this->m_data[i] += other_vecx->getValue(i);
    }
}

void palgox::palgox_vecx::subVecx(const palgox_vecx* other_vecx) {
    if (!this->isSameSize(other_vecx)) {
        throw palgoxException("Different number of elements");
    }
#pragma omp parallel for
    for (int i = 0; i < this->m_numElems; i++) {
        this->m_data[i] -= other_vecx->getValue(i);
    }
}

int palgox::palgox_vecx::search(const int value) const {
    int idx = -1;
#pragma omp parallel for
    for (int i = 0; i < this->m_numElems; i++) {
        if (idx != -1) continue;
        if (this->m_data[i] == value) {
#pragma omp critical
            {
                idx = i;
            }
        }
    }
    return idx;
}

void palgox::palgox_vecx::quickSort() {
    quickSortHelper(this->m_data, 0, this->m_numElems - 1);
}

void palgox::palgox_vecx::quickSortHelper(std::vector<int>& arr, const int low, const int high) {
    if(low<high) {
        const int mid = partition(arr,low,high);
        std::thread leftThread(&palgox_vecx::quickSortHelper, this, std::ref(arr), low, mid - 1);
        std::thread rightThread(&palgox_vecx::quickSortHelper, this, std::ref(arr), mid + 1, high);
        leftThread.join();
        rightThread.join();
    }
}

int palgox::palgox_vecx::partition(std::vector<int>& arr, const int low, const int high) {
    const int pivot = arr[high];
    int i = low-1;
    for (int j = low; j <= high - 1; j++) {
        if(arr[j] < pivot) {
            i++;
            std::swap(arr[i],arr[j]);
        }
    }
    std::swap(arr[i+1], arr[high]);
    return (i+1);
}

void palgox::palgox_vecx::mergeSort() {
    mergeSortHelper(this->m_data, 0, this->m_numElems - 1);
}

void palgox::palgox_vecx::mergeSortHelper(std::vector<int>& arr, const int begin, const int end) {
    if (begin >= end) {
        return;
    }
    const int mid = begin + (end - begin) / 2;
    std::thread leftThread(&palgox_vecx::mergeSortHelper, this, std::ref(arr), begin, mid);
    std::thread rightThread(&palgox_vecx::mergeSortHelper, this, std::ref(arr), mid + 1, end);
    leftThread.join();
    rightThread.join();
    merge(arr, begin, mid, end);
}

void palgox::palgox_vecx::merge(std::vector<int>& arr, const int left, const int mid, const int right) {
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    auto* leftArray = new int[subArrayOne];
    auto* rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++) {
        leftArray[i] = arr[left + i];
    }
    for (auto j = 0; j < subArrayTwo; j++) {
        rightArray[j] = arr[mid + 1 + j];
    }

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

palgox::palgox_vecx* palgox::palgox_vecx::filter(bool (*operation)(int)) const {
    std::vector<int> result_vector(this->m_numElems);
    std::vector result_indices(this->m_numElems, -1);
    const int numThreads = static_cast<int>(std::thread::hardware_concurrency());
    std::vector<std::thread> threads;
    const int chunkSize = (this->m_numElems + numThreads - 1) / numThreads;
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = std::min(start + chunkSize, this->m_numElems);
        threads.emplace_back([&, start, end]() {
            for (int i = start; i < end; ++i) {
                if (operation(this->m_data[i])) {
                    result_indices[i] = 1;
                }
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
    int result_index = 0;
    for (int i = 0; i < this->m_numElems; ++i) {
        if (result_indices[i] != -1) {
            result_vector[result_index++] = this->m_data[i];
        }
    }
    result_vector.resize(result_index);
    if (result_vector.empty()) {
        throw palgoxException("Empty result output");
    }
    return new palgox_vecx(result_vector);
}

bool palgox::palgox_vecx::andMap(bool (*operation)(int)) const {
    bool result = true;
#pragma omp parallel for
    for (int i = 0; i < this->m_numElems; i++) {
        if (!result) continue;
        if (!operation(this->m_data[i])) {
#pragma omp critical
            {
                result = false;
            }
        }
    }
    return result;
}

bool palgox::palgox_vecx::orMap(bool (*operation)(int)) const {
    bool result = false;
#pragma omp parallel for
    for (int i = 0; i < this->m_numElems; i++) {
        if (result) continue;
        if (operation(this->m_data[i])) {
#pragma omp critical
            {
                result = true;
            }
        }
    }
    return result;
}

int palgox::palgox_vecx::findMin() const {
    int min_elem = INT32_MAX;
#pragma omp parallel for reduction(min:min_elem)
    for (int i = 0; i < m_numElems; i++) {
        min_elem = std::min(min_elem, m_data[i]);
    }
    return min_elem;
}

int palgox::palgox_vecx::findMax() const {
    int max_elem = INT32_MIN;
#pragma omp parallel for reduction(max:max_elem)
    for (int i = 0; i < m_numElems; i++) {
        max_elem = std::max(max_elem, m_data[i]);
    }
    return max_elem;
}

int palgox::palgox_vecx::reduceLeft(const int init, int (*operation)(int, int)) const {
    int result = init;
#pragma omp parallel for reduction(+:result)
    for (int i = 0; i < this->m_numElems; ++i) {
        result = operation(result, m_data[i]);
    }
    return result;
}

int palgox::palgox_vecx::reduceRight(const int init, int (*operation)(int, int)) const {
    // TODO: SEQUENTIAL VERSION, make multithreaded ?
    int result = init;
    for (int i = this->m_numElems - 1; i >= 0; i--) {
        result = operation(result, m_data[i]);
    }
    return result;
}

palgox::palgox_vecx* palgox::palgox_vecx::prefixSum() const {
    // TODO: SEQUENTIAL VERSION, make multithreaded ?
    std::vector result_vector(this->m_numElems, this->m_data[0]);
    for (int i = 1; i < this->m_numElems; i++) {
        result_vector[i] = result_vector[i - 1] + this->m_data[i];
    }
    return new palgox_vecx(result_vector);
}

palgox::palgox_vecx* palgox::palgox_vecx::suffixSum() const {
    // TODO: SEQUENTIAL VERSION, make multithreaded ?
    std::vector result_vector(this->m_numElems, this->m_data[this->m_numElems - 1]);
    for (int i = this->m_numElems - 2; i >= 0; i--) {
        result_vector[i] = result_vector[i + 1] + this->m_data[i];
    }
    return new palgox_vecx(result_vector);
}

/*
 *
 *  PAlgoX_MatX implementations
 *
 */

// Constructor
palgox::palgox_matx::palgox_matx(const std::vector<std::vector<int>>& input_data) {
    if (input_data.empty()) throw palgoxException("Input data is empty");
    this->m_data = input_data;
    const int num_cols = static_cast<int>(input_data[0].size());
#pragma omp parallel for
    for (const auto& row : input_data) {
        if (row.size() != num_cols) {
            throw palgoxException("Input data has inconsistent column count");
        }
    }
    this->m_numRow = static_cast<int>(m_data.size());
    this->m_numCol = num_cols;
}

int palgox::palgox_matx::getNumRows() const {
    return this->m_numRow;
}

int palgox::palgox_matx::getNumCols() const {
    return this->m_numCol;
}

int palgox::palgox_matx::getValue(const int row, const int col) const {
    if ((row >= this->getNumRows() || row < 0) || (col >= this->getNumCols() || col < 0)) {
        throw palgoxException("Out of bounds: row or column value");
    }
    return this->m_data[row][col];
}

bool palgox::palgox_matx::isSameShape(const palgox_matx* other_matx) const {
    return !(other_matx->getNumRows() != this->m_numRow ||
        other_matx->getNumCols() != this->m_numCol);
}

bool palgox::palgox_matx::isEqual(const palgox_matx* other_matx) const {
    if (!this->isSameShape(other_matx)) return false;
    bool result = true;
#pragma omp parallel for collapse(2) shared(result)
    for (int i = 0; i < this->m_numRow; ++i) {
        for (int j = 0; j < this->m_numCol; ++j) {
            if (!result) continue;
            if (this->m_data[i][j] != other_matx->getValue(i, j)) {
#pragma omp critical
                {
                    result = false;
                }
            }
        }
    }
    return result;
}

void palgox::palgox_matx::applyOperation(const palgox_matx* other_matx, int (*operation)(int, int)) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < this->m_numRow; ++i) {
        for (int j = 0; j < this->m_numCol; ++j) {
            this->m_data[i][j] = operation(this->m_data[i][j], other_matx->getValue(i, j));
        }
    }
}

void palgox::palgox_matx::addMatx(const palgox_matx* other_matx) {
    if (!this->isSameShape(other_matx)) {
        throw palgoxException("Different size matrices");
    }
    this->applyOperation(other_matx, [](const int a, const int b) {return a + b;});
}

void palgox::palgox_matx::subMatx(const palgox_matx* other_matx) {
    if (!this->isSameShape(other_matx)) {
        throw palgoxException("Different size matrices");
    }
    this->applyOperation(other_matx, [](const int a, const int b) {return a - b;});
}

palgox::palgox_matx* palgox::palgox_matx::getTranspose() const {
    std::vector<std::vector<int>> transposed_data(m_numCol, std::vector<int>(m_numRow));
#pragma omp parallel for collapse(2)
    for (int i = 0; i < m_numRow; ++i) {
        for (int j = 0; j < m_numCol; ++j) {
            transposed_data[j][i] = m_data[i][j];
        }
    }
    auto* ret_matx = new palgox_matx(transposed_data);
    return ret_matx;
}

palgox::palgox_matx* palgox::palgox_matx::mulMatx(const palgox_matx* other_matx) const {
    if (this->m_numCol != other_matx->getNumRows()) {
        throw palgoxException("No matching dimensions for multiplication");
    }
    std::vector<std::vector<int>> retval_data(this->m_numRow, std::vector<int>(other_matx->getNumCols()));
#pragma omp parallel for collapse(2)
    for (int i = 0; i < this->m_numRow; i++) {
        for (int j = 0; j < other_matx->getNumCols(); j++) {
            int sum = 0;
#pragma omp parallel for reduction(+:sum)
            for (int k = 0; k < this->getNumCols(); k++) {
                sum += (this->m_data[i][k] * other_matx->getValue(k, j));
            }
            retval_data[i][j] = sum;
        }
    }
    auto* ret_matx = new palgox_matx(retval_data);
    return ret_matx;
}

bool palgox::palgox_matx::andMap(bool (*operation)(int)) const {
    bool result = true;
#pragma omp parallel for collapse(2) reduction(&&:result)
    for (int i = 0; i < this->m_numRow; i++) {
        for (int j = 0; j < this->m_numCol; j++) {
            if (!result) continue;
            if (!operation(this->m_data[i][j])) {
#pragma omp critical
                {
                    result = false;
                }
            }
        }
    }
    return result;
}

bool palgox::palgox_matx::orMap(bool (*operation)(int)) const {
    bool result = false;
#pragma omp parallel for collapse(2) reduction(||:result)
    for (int i = 0; i < this->m_numRow; i++) {
        for (int j = 0; j < this->m_numCol; j++) {
            if (result) continue;
            if (operation(this->m_data[i][j])) {
#pragma omp critical
                {
                    result = true;
                }
            }
        }
    }
    return result;
}

/*
 *
 *  PAlgoX_GraphX implementations
 *
 */
palgox::palgox_graphx::palgox_graphx(const int numVertices) {
    if (numVertices <= 0) {
        throw palgoxException("Input size must be positive");
    }
    this->m_numVertices = numVertices;
    this->m_numEdges = 0;
#pragma omp parallel for
    for (int i = 0; i < this->m_numVertices; i++) {
        this->m_adjList[i] = std::unordered_set<int>();
    }
}

void palgox::palgox_graphx::addEdge(const int src_node, const int dest_node) {
    if (this->m_adjList.find(src_node) == this->m_adjList.end() || this->m_adjList.find(dest_node) == this->m_adjList.end()) {
        throw palgoxException("Invalid source or destination node");
    }
    if (this->m_adjList[src_node].find(dest_node) == this->m_adjList[src_node].end()) {
        this->m_adjList[src_node].insert(dest_node);
        this->m_adjList[dest_node].insert(src_node);
        this->m_numEdges++;
    }
}

std::unordered_set<int> palgox::palgox_graphx::getNeighboringNodes(const int node) const {
    if (this->m_adjList.find(node) == this->m_adjList.end()) {
        throw palgoxException("Invalid parameter node");
    }
    return this->m_adjList.at(node);
}

int palgox::palgox_graphx::getNumVertices() const {
    return this->m_numVertices;
}

bool palgox::palgox_graphx::isEqual(const palgox_graphx* other_graphx) const {
    if (this->m_numVertices != other_graphx->getNumVertices()) return false;
    bool result = true;
#pragma omp parallel for shared(result)
    for (int i = 0; i < this->m_numVertices; i++) {
        if (!result) continue;
        const std::unordered_set<int>& other_neighbors = other_graphx->getNeighboringNodes(i);
        if (this->m_adjList.at(i).size() != other_neighbors.size()) {
            // inconsistent neighboring nodes size
#pragma omp critical
            {
                result = false;
            }
            continue;
        }
        const auto& neighbors = this->m_adjList.at(i);
        for (const int& neighbor : neighbors) {
            if (other_neighbors.find(neighbor) == other_neighbors.end()) {
#pragma omp critical
                {
                    result = false;
                }
                break;
            }
        }
#pragma omp cancellation point for
    }
    return result;
}

bool palgox::palgox_graphx::hasCycle() {
    std::vector<bool> visited(this->m_numVertices, false);
    bool has_cycle = false;

#pragma omp parallel for shared(visited, has_cycle)
    for (int vertex = 0; vertex < this->m_numVertices; vertex++) {
        if (!visited[vertex]) {
#pragma omp critical
            {
                if (!visited[vertex] && !has_cycle) {
                    if (this->hasCycleHelper(vertex, visited, -1)) {
                        has_cycle = true;
                    }
                }
            }
        }
    }
    return has_cycle;
}

bool palgox::palgox_graphx::hasCycleHelper(const int vertex, std::vector<bool>& visited, const int parent) {
    visited[vertex] = true;
    for (const int& neighbor : this->m_adjList[vertex]) {
        if (!visited[neighbor]) {
            if (this->hasCycleHelper(neighbor, visited, vertex)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }
    return false;
}