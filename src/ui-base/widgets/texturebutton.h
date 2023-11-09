#ifndef TEXTUREBUTTON_H
#define TEXTUREBUTTON_H

#include <optional>

#include "coords/coordinates.h"

#include "basewidget.h"
#include "basemouseinteractor.h"
#include "../texture.h"

namespace UiBase
{
    class TextureButton :
        public BaseWidget,
        public BaseMouseInteractor
    {
        private:
            Texture normal;
            std::optional<Texture> mouseOver;
            std::optional<Texture> clicked;

        public:
            TextureButton(Coords::PixelCoordinates pos, Texture&& texture);
            static TextureButton fromFile(Coords::PixelCoordinates pos, const std::string& path);

            void setTextureNormal(const std::string& path);
            void setTextureMouseOver(const std::string& path);
            void clearTextureMouseOver();
            void setTextureClicked(const std::string& path);
            void clearTextureClicked();

            // Widget interface
            virtual const Texture& render() const;

    };
}

#endif // BASEBUTTON_H
