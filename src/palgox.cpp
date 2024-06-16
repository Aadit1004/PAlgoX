#include "palgox.h"

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
            if (this->m_data[i][j] != other_matx->getValue(i, j)) {
#pragma omp atomic write
                result = false;
#pragma omp cancel for
            }
        }
    }
#pragma omp cancellation point for
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
            if (!operation(this->m_data[i][j])) {
#pragma omp atomic write
                result = false;
#pragma omp cancel for
            }
        }
    }
#pragma omp cancellation point for
    return result;
}

bool palgox::palgox_matx::orMap(bool (*operation)(int)) const {
    bool result = false;
#pragma omp parallel for collapse(2) reduction(||:result)
    for (int i = 0; i < this->m_numRow; i++) {
        for (int j = 0; j < this->m_numCol; j++) {
            if (operation(this->m_data[i][j])) {
#pragma omp atomic write
                result = true;
#pragma omp cancel for
            }
        }
    }
#pragma omp cancellation point for
    return result;
}

/*
 *
 *  PAlgoX_VecX implementations
 *
 */

palgox::palgox_vecx::palgox_vecx(const std::vector<int>& input_data) {
    if (input_data.empty()) throw palgoxException("Input data is empty");
    this->m_numElems = static_cast<int>(input_data.size());
    this->m_data = input_data;
}

bool palgox::palgox_vecx::isEqual(const palgox_vecx* other_vecx) const {
    if (this->m_numElems != other_vecx->getNumElems()) return false;
    bool result = true;
#pragma omp parallel for shared(result)
    for (int idx = 0; idx < this->m_numElems; idx++) {
        if (this->m_data[idx] != other_vecx->getValue(idx)) {
#pragma omp atomic write // prevents race conditions in writing
            result = false;
#pragma omp cancel for
        }
    }
#pragma omp cancellation point for
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