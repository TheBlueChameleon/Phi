#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <stdexcept>

namespace Physics
{
    class DimensionError : public std::runtime_error
    {
        public:
            DimensionError(const std::string& message);
    };

    class CoordinatesError : public std::runtime_error
    {
        public:
            CoordinatesError(const std::string& message);
    };
}

#endif // ERRORS_H
