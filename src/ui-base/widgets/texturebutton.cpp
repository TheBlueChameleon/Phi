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

    void TextureButton::setTextureNormal(const std::string& path)
    {
        normal = Texture::fromFile(path);
        setSize(normal.getSize());
    }

    void TextureButton::setTextureMouseOver(const std::string& path)
    {
        // TODO: size check
        mouseOver.emplace(Texture::fromFile(path));
    }

    void TextureButton::clearTextureMouseOver()
    {
        // TODO: size check
        mouseOver.reset();
    }

    void TextureButton::setTextureClicked(const std::string& path)
    {
        clicked.emplace(Texture::fromFile(path));
    }

    void TextureButton::clearTextureClicked()
    {
        clicked.reset();
    }

    const Texture& TextureButton::render() const
    {
        const Texture* texture;
        switch (getMouseButtonState())
        {
            case MouseButtonState::Normal:
                {
                    PixelCoordinates mousePos;
                    PixelCoordinates upperLeft = this->getPosition();
                    PixelCoordinates lowerRight = this->getPosition() + this->getSize() - PixelCoordinates{1,1};
                    SDL_GetMouseState(&mousePos.x, &mousePos.y);

                    if (isWithin(mousePos, upperLeft, lowerRight))
                    {
                        // *INDENT-OFF*
                        if (mouseOver.has_value())  {texture = &*mouseOver;}
                        else                        {texture = &normal;}
                        // *INDENT-ON*
                    }
                    else
                    {
                        texture = &normal;
                    }
                }
                break;
            case MouseButtonState::Clicked:
            case MouseButtonState::Dragged:
                // *INDENT-OFF*
                if (clicked.has_value())    {texture = &*clicked;}
                else                        {texture = &normal;}
                // *INDENT-ON*
                break;
        }

        return *texture;
    }
}
