#ifndef PALGOX_LIBRARY_H
#define PALGOX_LIBRARY_H

#include <utility>
#include <vector>
#include <exception>
#include <string>
#include <iostream>

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

}

#endif //PALGOX_LIBRARY_H
