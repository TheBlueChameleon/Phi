#include "dragsubstitute.h"
#include <iostream>

namespace UiBase
{
    DragSubstitute::DragSubstitute(Widget& original, Coords::PixelCoordinates mouseOffset) :
        BaseWidget(original.getPosition(), original.getSize()),
        original(original),
        texture(original.render()),
        mouseOffset(mouseOffset)
    {
        texture.setAlpha(127);
        setMouseButtonState(MouseButtonState::Dragged);
    }

    DragSubstitute::~DragSubstitute()
    {
        std::cout << "kill the substitute @ " << this << std::endl;
    }

    Coords::PixelCoordinates DragSubstitute::getMouseOffset() const
    {
        return mouseOffset;
    }

    Widget& DragSubstitute::getOriginal() const
    {
        return original;
    }

    const Texture& DragSubstitute::render() const
    {
        return texture;
    }
}
