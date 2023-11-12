#include "util.h"

using namespace Base;

namespace UiBase
{
    Base::PixelCoordinates getAlignedBoxCoordinate(const Base::PixelCoordinates& containingSize, const Base::PixelCoordinates& boxSize, const HorizontalAlignment hAlignment,
                                                   const VerticalAlignment vAlignment)
    {
        PixelCoordinates renderPosition;
        switch (hAlignment)
        {
            case HorizontalAlignment::Left:
                renderPosition.x = 0;
                break;

            case HorizontalAlignment::Center:
                renderPosition.x = (containingSize.x - boxSize.x) / 2;
                break;

            case HorizontalAlignment::Right:
                renderPosition.x = containingSize.x - boxSize.x;
                break;
        }

        switch (vAlignment)
        {
            case VerticalAlignment::Top:
                renderPosition.y = 0;
                break;

            case VerticalAlignment::Center:
                renderPosition.y = (containingSize.y - boxSize.y) / 2;
                break;

            case VerticalAlignment::Bottom:
                renderPosition.y = containingSize.y - boxSize.y;
                break;
        }

        return renderPosition;
    }
}
