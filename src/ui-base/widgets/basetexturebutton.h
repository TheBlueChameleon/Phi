#ifndef BASETEXTUREBUTTON_H
#define BASETEXTUREBUTTON_H

#include <optional>

#include "coords/coordinates.h"

#include "basewidget.h"
#include "basemouseinteractor.h"
#include "../texture.h"

namespace UiBase
{
    class BaseTextureButton :
        public BaseWidget,
        public BaseMouseInteractor
    {
        private:
            Texture normal;
            std::optional<Texture> mouseOver;
            std::optional<Texture> clicked;

            BaseTextureButton(Coords::PixelCoordinates pos, Texture&& texture);

        public:
            BaseTextureButton(Coords::PixelCoordinates pos, Coords::PixelCoordinates size);

            static BaseTextureButton fromFile(Coords::PixelCoordinates pos, const std::string& path);

            void setTextureNormal(const std::string& path);
            void setTextureMouseOver(const std::string& path);
            void clearTextureMouseOver();
            void setTextureClicked(const std::string& path);
            void clearTextureClicked();

            // Widget interface
            virtual void render() const;

    };
}

#endif // BASEBUTTON_H
