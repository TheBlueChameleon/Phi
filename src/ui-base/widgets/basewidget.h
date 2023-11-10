#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include "widget.h"

namespace UiBase
{
    class BaseWidget : public Widget
    {
        private:
            bool visible = true;
            bool active = true;
            Base::PixelCoordinates position;
            Base::PixelCoordinates size;

        public:
            BaseWidget(const Base::PixelCoordinates& position, const Base::PixelCoordinates& size);
            ~BaseWidget();

            // Widget interface
            bool isVisible() const;
            void makeVisible();
            void makeInvisible();

            bool isActive() const;
            void makeActive();
            void makeInactive();

            Base::PixelCoordinates getPosition() const;
            void setPosition(const Base::PixelCoordinates& pos);
            Base::PixelCoordinates getSize() const;
            void setSize(const Base::PixelCoordinates& size);
    };
}

#endif // BASEWIDGET_H
