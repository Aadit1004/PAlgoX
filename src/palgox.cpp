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
    return this->m_data[row][col];
}

bool palgox::palgox_matx::isSameShape(const palgox_matx* other_matx) const {
    return !(other_matx->getNumRows() != this->m_numRow ||
        other_matx->getNumCols() != this->m_numCol);
}


bool palgox::palgox_matx::isEqual(const palgox_matx* other_matx) const {
    if (!this->isSameShape(other_matx)) return false;
    for (int i = 0; i < this->m_numRow; ++i) {
#pragma omp parallel for
        for (int j = 0; j < this->m_numCol; ++j) {
            if (this->m_data[i][j] != other_matx->getValue(i, j)) return false;
        }
    }
    return true;
}

void palgox::palgox_matx::applyOperation(const palgox_matx* other_matx, int (*operation)(int, int)) {
    for (int i = 0; i < this->m_numRow; ++i) {
#pragma omp parallel for
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
