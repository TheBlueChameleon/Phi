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
            virtual void render() const;

            // MouseInteractor interface
            virtual void onMouseButton(const SDL_MouseButtonEvent& e);
            virtual void onMouseOver(const SDL_MouseMotionEvent& e);
            virtual void onMouseWheel(const SDL_MouseWheelEvent& e);

            virtual void onClick(const SDL_MouseButtonEvent& e);

    };
}

#endif // BASEBUTTON_H
