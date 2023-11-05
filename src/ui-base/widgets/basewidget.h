#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include "widget.h"

namespace UiBase
{
    class BaseWidget : public Widget
    {
        private:
            bool visible = true;
            Coords::PixelCoordinates position;
            Coords::PixelCoordinates size;

        public:
            BaseWidget(const Coords::PixelCoordinates& position, const Coords::PixelCoordinates& size);
            ~BaseWidget();

            // Widget interface
            bool isVisible() const;
            void makeVisible();
            void makeInvisible();

            Coords::PixelCoordinates getPosition() const;
            void setPosition(const Coords::PixelCoordinates& pos);
            Coords::PixelCoordinates getSize() const;
            void setSize(const Coords::PixelCoordinates& size);
    };
}

#endif // BASEWIDGET_H
