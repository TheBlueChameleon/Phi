#include <iostream>

#include "basetexturebutton.h"

namespace UiBase
{
    using namespace ::Coords;

    BaseTextureButton::BaseTextureButton(PixelCoordinates pos, Texture&& texture) :
        BaseWidget(pos, texture.getSize()),
        normal(std::move(texture))
    {}

    BaseTextureButton::BaseTextureButton(PixelCoordinates pos, PixelCoordinates size) :
        BaseWidget(pos, size),
        normal(Texture(size.x, size.y))
    {}

    BaseTextureButton BaseTextureButton::fromFile(PixelCoordinates pos, const std::string& path)
    {
        Texture t(Texture::fromFile(path));
        return BaseTextureButton(pos, std::move(t));
    }

    void BaseTextureButton::setTextureNormal(const std::string& path)
    {
        normal = Texture::fromFile(path);
        setSize(normal.getSize());
    }

    void BaseTextureButton::setTextureMouseOver(const std::string& path)
    {
        // TODO: size check
        mouseOver.emplace(Texture::fromFile(path));
    }

    void BaseTextureButton::clearTextureMouseOver()
    {
        // TODO: size check
        mouseOver.reset();
    }

    void BaseTextureButton::setTextureClicked(const std::string& path)
    {
        clicked.emplace(Texture::fromFile(path));
    }

    void BaseTextureButton::clearTextureClicked()
    {
        clicked.reset();
    }

    void BaseTextureButton::render() const
    {
        const Texture* texture;
        switch (getMouseButtonState())
        {
            case MouseButtonState::Normal:
                {
                    Coords::PixelCoordinates mousePos;
                    Coords::PixelCoordinates upperLeft = this->getPosition();
                    Coords::PixelCoordinates lowerRight = this->getPosition() + this->getSize() - Coords::PixelCoordinates{1,1};
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

        texture->renderAt(getPosition());
    }
}
