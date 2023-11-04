#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <stdexcept>

namespace Base
{
    class PhiError : public std::runtime_error
    {
        public:
            PhiError(const std::string& message);
    };
}

#define DEF_ERROR(__name__) class __name__ : public Base::PhiError { public: __name__(const std::string& message); }

namespace Coords
{
    DEF_ERROR(DimensionError);
    DEF_ERROR(CoordinatesError);
}

namespace Physics
{
}

namespace UiBase
{
    DEF_ERROR(SdlError);
}

#undef DEF_ERROR
#endif // ERRORS_H
