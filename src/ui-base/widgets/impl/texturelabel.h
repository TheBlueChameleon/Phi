#ifndef TEXTURELABEL_H
#define TEXTURELABEL_H

#include <optional>

#include <SDL2/SDL_ttf.h>

#include "basewidget.h"
#include "ui-base/base/alignment.h"

namespace UiBase
{
    class TextureLabel :
        BaseWidget
    {
        private:
            std::string text;
            TTF_Font*   font;
            SDL_Color   color = SdlColors::black;
            HorizontalAlignment hAlignment = HorizontalAlignment::Left;
            VerticalAlignment vAlignment   = VerticalAlignment::Top;

            std::optional<Texture> backdrop;

            Texture texture;
            bool renderingSuspended = false;

            void updateTexture();

        public:
            TextureLabel(const Base::PixelCoordinates& pos, const Base::PixelCoordinates& size, const std::string& fontID);

            const std::string&  getText() const;
            void                setText(const std::string& newText);

            TTF_Font*           getFont() const;
            void                setFont(const std::string& fontID);

            const SDL_Color&    getColor() const;
            void                setColor(const SDL_Color& newColor);

            HorizontalAlignment getHAlignment() const;
            void                setHAlignment(HorizontalAlignment newHAlignment);

            VerticalAlignment   getVAlignment() const;
            void                setVAlignment(VerticalAlignment newVAlignment);

            const std::optional<Texture>&   getBackdrop() const;
            void                            setBackdrop(const Texture& newBackdrop);
            void                            setBackdrop(Texture&& newBackdrop);
            void                            clearBackdrop();

            const Texture& getTexture() const;

            void suspendUpdateRendering();
            void resumeUpdateRendering();

            // Widget interface
            const Texture& render() const;

            void setSize(const Base::PixelCoordinates& size);
    };
}

#endif // TEXTURELABEL_H
