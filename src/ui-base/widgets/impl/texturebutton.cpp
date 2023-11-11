#include <iostream>

#include "texturebutton.h"

using namespace Base;
namespace UiBase
{
    TextureButton::TextureButton(PixelCoordinates pos, Texture&& texture) :
        BaseWidget(pos, texture.getSize()),
        normal(std::move(texture))
    {}

    TextureButton TextureButton::fromFile(PixelCoordinates pos, const std::string& path)
    {
        return TextureButton(pos, Texture::fromFile(path));
    }

    void TextureButton::setTextureNormal(const Texture& texture)
    {
        normal = texture;
        setSize(normal.getSize());
        clearIfNonMatchingSize();
    }

    void TextureButton::setTextureNormal(Texture&& texture)
    {
        normal = std::move(texture);
        setSize(normal.getSize());
        clearIfNonMatchingSize();
    }

    void TextureButton::throwIfNonMatchingSize(const Texture& other) const
    {
        if (normal.getSize() != other.getSize())
        {
            throw DimensionError("Dimensions of default texture and alternative do not match!");
        }
    }

    void TextureButton::clearIfNonMatchingSize()
    {
        if (clicked.has_value() && normal.getSize() != clicked.value().getSize())
        {
            clearTextureClicked();
        }

        if (mouseOver.has_value() && normal.getSize() != mouseOver.value().getSize())
        {
            clearTextureMouseOver();
        }
    }

    void TextureButton::setTextureMouseOver(const Texture& texture)
    {
        throwIfNonMatchingSize(texture);
        mouseOver = texture;
    }

    void TextureButton::setTextureMouseOver(Texture&& texture)
    {
        throwIfNonMatchingSize(texture);
        mouseOver = std::move(texture);
    }

    void TextureButton::clearTextureMouseOver()
    {
        mouseOver.reset();
    }

    void TextureButton::setTextureClicked(const Texture& texture)
    {
        throwIfNonMatchingSize(texture);
        clicked = texture;
    }

    void TextureButton::setTextureClicked(Texture&& texture)
    {
        throwIfNonMatchingSize(texture);
        clicked = std::move(texture);
    }

    void TextureButton::clearTextureClicked()
    {
        clicked.reset();
    }

    const Texture& TextureButton::render() const
    {
        if (hasMouseOver())
        {
            if (isClicked())
            {
                if (clicked.has_value())
                {
                    return clicked.value();
                }
            }
            if (mouseOver.has_value())
            {
                return mouseOver.value();
            }
        }

        return normal;

    }
}
