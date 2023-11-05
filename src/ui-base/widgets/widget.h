#ifndef WIDGET_H
#define WIDGET_H

#include "coords/coordinates.h"

namespace UiBase
{
    struct Widget
    {
        virtual bool isVisible() const = 0;
        virtual void makeVisible() = 0;
        virtual void makeInvisible() = 0;

        virtual Coords::PixelCoordinates getPosition() const = 0;
        virtual void setPosition(const Coords::PixelCoordinates& pos) = 0;
        virtual Coords::PixelCoordinates getSize() const = 0;
        virtual void setSize(const Coords::PixelCoordinates& pos) = 0;

        virtual void render() const = 0;
    };
}

#endif // WIDGET_H