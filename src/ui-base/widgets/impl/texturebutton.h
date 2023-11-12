#ifndef TEXTUREBUTTON_H
#define TEXTUREBUTTON_H

#include <optional>

#include "base/coordinates/coordinate.h"

#include "basewidget.h"
#include "ui-base/base/texture.h"

namespace UiBase
{
    class TextureButton :
        public BaseWidget
    {
        private:
            Texture normal;
            std::optional<Texture> mouseOver;
            std::optional<Texture> clicked;

            void throwIfNonMatchingSize(const Texture& other) const;
            void clearIfNonMatchingSize();

        public:
            TextureButton(const Base::PixelCoordinates& pos, const Texture& texture);
            TextureButton(const Base::PixelCoordinates& pos, Texture&& texture);
            static TextureButton fromFile(const Base::PixelCoordinates& pos, const std::string& path);

            void setTextureNormal(const Texture& texture);
            void setTextureNormal(Texture&& texture);
            void setTextureMouseOver(const Texture& texture);
            void setTextureMouseOver(Texture&& texture);
            void clearTextureMouseOver();
            void setTextureClicked(const Texture& texture);
            void setTextureClicked(Texture&& texture);
            void clearTextureClicked();

            // Widget interface
            virtual const Texture& render() const;

            void setSize(const Base::PixelCoordinates& size);
    };
}

#endif // BASEBUTTON_H
