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
        Texture t = Texture::fromFile(path);
        return BaseTextureButton(pos, std::move(t));
    }

    void BaseTextureButton::render() const
    {
        normal.renderAt(getPosition());
    }

    void BaseTextureButton::onMouseButton(const SDL_MouseButtonEvent& e)
    {
        std::cout << "click!" << std::endl;
    }

    void BaseTextureButton::onClick(const SDL_MouseButtonEvent& e) {}

    void BaseTextureButton::onMouseOver(const SDL_MouseMotionEvent& e) {}

    void BaseTextureButton::onMouseWheel(const SDL_MouseWheelEvent& e) {}
}
