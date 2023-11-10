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
            Base::PixelCoordinates mouseOffset;

        public:
            DragSubstitute(Widget& original, Base::PixelCoordinates mouseOffset);
            ~DragSubstitute();

            Base::PixelCoordinates getMouseOffset() const;
            Widget& getOriginal() const;

            // Widget interface
            const Texture& render() const;
    };
}

#endif // DRAGSUBSTITUTE_H
