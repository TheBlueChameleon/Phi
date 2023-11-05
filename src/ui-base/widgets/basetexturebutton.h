#ifndef BASETEXTUREBUTTON_H
#define BASETEXTUREBUTTON_H

#include <optional>

#include "coords/coordinates.h"

#include "basewidget.h"
#include "mouseinteractor.h"
#include "../texture.h"

namespace UiBase
{
    class BaseTextureButton :
        public BaseWidget,
        public MouseInteractor
    {
        private:
            Texture normal;
            std::optional<Texture> mouseOver;
            std::optional<Texture> clicked;

            BaseTextureButton(Coords::PixelCoordinates pos, Texture&& texture);

        public:
            BaseTextureButton(Coords::PixelCoordinates pos, Coords::PixelCoordinates size);

            static BaseTextureButton fromFile(Coords::PixelCoordinates pos, const std::string& path);

            // Widget interface
            void render() const;

            // MouseInteractor interface
            void onClick(const SDL_MouseButtonEvent& e);
            void onMouseOver(const SDL_MouseMotionEvent& e);
            void onMouseWheel(const SDL_MouseWheelEvent& e);
    };
}

#endif // BASEBUTTON_H
