#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <stdexcept>

class PhiError : public std::runtime_error
{
    public:
        PhiError(const std::string& message);
};

#define DEF_ERROR(__name__) class __name__ : public PhiError { public: __name__(const std::string& message); }

namespace Coords
{
    DEF_ERROR(DimensionError);
    DEF_ERROR(CoordinatesError);
}

namespace Physics
{
}

#undef DEF_ERROR
#endif // ERRORS_H
