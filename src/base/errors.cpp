#include "errors.h"

#define DEF_ERROR(__name__) __name__::__name__(const std::string& message) : Base::PhiError(message) {}

namespace Base
{
    PhiError::PhiError(const std::string& message) : std::runtime_error(message) {}
}

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
