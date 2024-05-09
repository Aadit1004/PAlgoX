#ifndef PALGOX_LIBRARY_H
#define PALGOX_LIBRARY_H

#include <utility>
#include <vector>
#include <exception>
#include <string>
#include <iostream>
#include <omp.h>

namespace palgox
{
    class palgoxException : public std::exception
    {
    private:
        std::string message;
    public:
        explicit palgoxException(std::string msg) : message(std::move(msg)) {}
        std::string what() { return message;}
    };

    class palgox_matx
    {
    private:
        std::vector<std::vector<int>> m_data;
        int m_numRow;
        int m_numCol;

    public:
        explicit palgox_matx(const std::vector<std::vector<int>>& input_data);

        bool isEqual(palgox_matx& other_matx);

        void addMatx(palgox_matx& other_matx);

        void subMatx(palgox_matx& other_matx);

        palgox_matx getTranspose();

        palgox_matx mulMatx(palgox_matx& other_matx);

        [[nodiscard]] int getNumRows() const;

        [[nodiscard]] int getNumCols() const;
    };

    class palgox_vecx
    {
    private:

    public:
    };

    class palgox_graphx
    {
    private:

    public:
    };
}

#endif //PALGOX_LIBRARY_H
