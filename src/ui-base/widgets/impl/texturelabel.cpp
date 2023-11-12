#include <iostream>

#include "texturelabel.h"
#include "ui-base/base/surface.h"

using namespace Base;

namespace UiBase
{
    TextureLabel::TextureLabel(const Base::PixelCoordinates& pos, const Base::PixelCoordinates& size, const std::string& fontID) :
        BaseWidget(pos, size)
    {
        font = rte.getFontOrThrow(fontID);

        if (size == PixelCoordinates({0,0}))
        {
            texture = Texture({1,1});
        }
        else
        {
            texture = Texture(size);
        }
    }

    const std::string& TextureLabel::getText() const
    {
        return text;
    }

    void TextureLabel::setText(const std::string& newText)
    {
        text = newText;
        updateTexture();
    }

    TTF_Font* TextureLabel::getFont() const
    {
        return font;
    }

    void TextureLabel::setFont(const std::string& fontID)
    {
        font = rte.getFontOrThrow(fontID);
        updateTexture();
    }

    const SDL_Color& TextureLabel::getColor() const
    {
        return color;
    }

    void TextureLabel::setColor(const SDL_Color& newColor)
    {
        color = newColor;
        updateTexture();
    }

    HorizontalAlignment TextureLabel::getHAlignment() const
    {
        return hAlignment;
    }

    void TextureLabel::setHAlignment(HorizontalAlignment newHAlignment)
    {
        hAlignment = newHAlignment;
        updateTexture();
    }

    VerticalAlignment TextureLabel::getVAlignment() const
    {
        return vAlignment;
    }

    void TextureLabel::setVAlignment(VerticalAlignment newVAlignment)
    {
        vAlignment = newVAlignment;
        updateTexture();
    }

    const std::optional<Texture>& TextureLabel::getBackdrop() const
    {
        return backdrop;
    }

    void TextureLabel::setBackdrop(const Texture& newBackdrop)
    {
        backdrop = newBackdrop;
        updateTexture();
    }

    void TextureLabel::setBackdrop(Texture&& newBackdrop)
    {
        backdrop = std::move(newBackdrop);
        setSize(newBackdrop.getSize());
        updateTexture();
    }

    void TextureLabel::clearBackdrop()
    {
        backdrop.reset();
        updateTexture();
    }

    const Texture& TextureLabel::getTexture() const
    {
        return texture;
    }

    void TextureLabel::suspendUpdateRendering()
    {
        renderingSuspended = true;
    }

    void TextureLabel::resumeUpdateRendering()
    {
        renderingSuspended = false;
        updateTexture();
    }

    void TextureLabel::updateTexture()
    {
        if (renderingSuspended)
        {
            return;
        }
        renderingSuspended = true;

        Texture textTexture = Surface::fromText(text, font, color, getSize().x).toTexture(SDL_TEXTUREACCESS_STATIC);

        if (backdrop.has_value())
        {
            texture = backdrop.value();
            textTexture.renderOntoCentered(texture);
        }
        else
        {
            texture = std::move(textTexture);
        }

        renderingSuspended = false;
    }

    const Texture& TextureLabel::render() const
    {
        return texture;
    }

    void TextureLabel::setSize(const Base::PixelCoordinates& size)
    {
        BaseWidget::setSize(size);
        if (size != backdrop->getSize())
        {
            backdrop.reset();
        }

        updateTexture();
    }
}
