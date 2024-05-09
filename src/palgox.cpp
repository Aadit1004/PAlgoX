#include "palgox.h"

/*
 *
 *  PAlgoX_MatX implementations
 *
 */

// Constructor
palgox::palgox_matx::palgox_matx(const std::vector<std::vector<int>>& input_data)
{
    if (input_data.empty()) throw palgoxException("Input data is empty");
    m_data = input_data;
    const int num_cols = static_cast<int>(input_data[0].size());
#pragma omp parallel for
    for (const auto& row : input_data) {
        if (row.size() != num_cols) {
            throw palgoxException("Input data has inconsistent column count");
        }
    }
    m_numRow = static_cast<int>(m_data.size());
    m_numCol = num_cols;
}

int palgox::palgox_matx::getNumRows() const
{
    return m_numRow;
}

int palgox::palgox_matx::getNumCols() const
{
    return m_numCol;
}
