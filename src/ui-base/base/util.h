#ifndef UTIL_H
#define UTIL_H

#include "alignment.h"
#include "base/coordinates/coordinate.h"

namespace UiBase
{
    Base::PixelCoordinates getAlignedBoxCoordinate(const Base::PixelCoordinates& containingSize, const Base::PixelCoordinates& boxSize,
                                                   const HorizontalAlignment hAlignment, const VerticalAlignment vAlignment);
}

#endif // UTIL_H
