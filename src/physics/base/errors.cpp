#include "errors.h"

namespace Physics
{
    DimensionError::DimensionError(const std::string& message) : std::runtime_error(message) {}
    CoordinatesError::CoordinatesError(const std::string& message) : std::runtime_error(message) {}
}
