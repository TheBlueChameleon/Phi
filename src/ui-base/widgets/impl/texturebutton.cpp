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
        Texture t(Texture::fromFile(path));
        return TextureButton(pos, std::move(t));
    }

    void TextureButton::setTextureNormal(const Texture& texture)
    {
        normal = texture;
        setSize(normal.getSize());
    }

    void TextureButton::setTextureMouseOver(const Texture& texture)
    {
        // TODO: size check
        mouseOver = texture;
    }

    void TextureButton::clearTextureMouseOver()
    {
        // TODO: size check
        mouseOver.reset();
    }

    void TextureButton::setTextureClicked(const Texture& texture)
    {
        clicked = texture;
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
