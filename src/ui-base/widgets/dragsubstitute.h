#ifndef DRAGSUBSTITUTE_H
#define DRAGSUBSTITUTE_H

#include "basemouseinteractor.h"
#include "basewidget.h"

namespace UiBase
{
    class DragSubstitute :
        public BaseWidget,
        public BaseMouseInteractor
    {
        private:
            Widget& original;
            Texture texture;
            Coords::PixelCoordinates mouseOffset;

        public:
            DragSubstitute(Widget& original, Coords::PixelCoordinates mouseOffset);
            ~DragSubstitute();

            Coords::PixelCoordinates getMouseOffset() const;
            Widget& getOriginal() const;

            // Widget interface
            const Texture& render() const;
    };
}

#endif // DRAGSUBSTITUTE_H
