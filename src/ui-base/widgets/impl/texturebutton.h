#ifndef TEXTUREBUTTON_H
#define TEXTUREBUTTON_H

#include <optional>

#include "base/coordinates/coordinate.h"

#include "ui-base/base/texture.h"
#include "ui-base/widgets/impl/basewidget.h"

namespace UiBase
{
    class TextureButton :
        public BaseWidget
    {
        private:
            Texture normal;
            std::optional<Texture> mouseOver;
            std::optional<Texture> clicked;

        public:
            TextureButton(Base::PixelCoordinates pos, Texture&& texture);
            static TextureButton fromFile(Base::PixelCoordinates pos, const std::string& path);

            void setTextureNormal(const Texture& texture);
            void setTextureMouseOver(const Texture& texture);
            void clearTextureMouseOver();
            void setTextureClicked(const Texture& texture);
            void clearTextureClicked();

            // Widget interface
            virtual const Texture& render() const;

    };
}

#endif // BASEBUTTON_H
