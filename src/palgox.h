#ifndef PALGOX_LIBRARY_H
#define PALGOX_LIBRARY_H

#include <utility>
#include <vector>
#include <exception>
#include <string>
#include <iostream>
#include <omp.h>
#include <thread>

namespace palgox {
    class palgoxException final : public std::exception {
    private:
        std::string message;
    public:
        explicit palgoxException(std::string msg) : message(std::move(msg)) {}
        std::string what() { return message;}
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
    };

    class palgox_vecx {
    private:
        std::vector<int> m_data;
        int m_numElems;
    public:
        explicit palgox_vecx(const std::vector<int>& input_data);
        bool isEqual(const palgox_vecx* other_vecx) const;
        // map, foldlm filter funcs?
    };

    class palgox_graphx {
    private:

    public:
    };
}

#endif //PALGOX_LIBRARY_H
