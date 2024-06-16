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

        // TODO functions:
        // TODO functions:
        // TODO functions:

        bool andMap(bool (*operation)(int)) const;

        bool orMap(bool (*operation)(int)) const;

    };

    class palgox_vecx {
    private:
        std::vector<int> m_data;
        int m_numElems;

        bool isSameSize(const palgox_vecx* other_vecx) const;
    public:
        explicit palgox_vecx(const std::vector<int>& input_data);

        explicit palgox_vecx(int size, int (*operation)(int));

        bool isEqual(const palgox_vecx* other_vecx) const;

        [[nodiscard]] int getNumElems() const;

        [[nodiscard]] int getValue(int idx) const;

        void applyOperation(int (*operation)(int, int));

        void addVecx(const palgox_vecx* other_vecx);

        void subVecx(const palgox_vecx* other_vecx);

        void quickSort();

        void mergeSort();

        int search(int value);

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

    class palgox_graphx {
    private:

    public:
    };
}

#endif //PALGOX_LIBRARY_H
