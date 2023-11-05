#include "basemouseinteractor.h"

namespace UiBase
{
    BaseMouseInteractor::MouseButtonState BaseMouseInteractor::getMouseButtonState() const
    {
        return mouseButtonState;
    }

    void BaseMouseInteractor::onMouseButton(const SDL_MouseButtonEvent& e)
    {
        // *INDENT-OFF*
        if      (e.state == SDL_PRESSED)    {mouseButtonState = MouseButtonState::Clicked; onClick(e);}
        else if (e.state == SDL_RELEASED)
        {
            if (mouseButtonState == MouseButtonState::Dragged)    {mouseButtonState = MouseButtonState::Normal; onDrop(e);}
            else                            {mouseButtonState = MouseButtonState::Normal;}
        }
        // *INDENT-ON*
    }

    void BaseMouseInteractor::onMouseMotion(const SDL_MouseMotionEvent& e)
    {
        switch (mouseButtonState)
        {
            case MouseButtonState::Normal:
                onMouseOver(e);
                break;
            case MouseButtonState::Clicked:
                mouseButtonState = MouseButtonState::Dragged;
                onDrag(e);
                break;
            case MouseButtonState::Dragged:
                mouseButtonState = MouseButtonState::Dragged;
                onDrag(e);
                break;
        }
    }

    void BaseMouseInteractor::onMouseWheel(const SDL_MouseWheelEvent& e) {}
    void BaseMouseInteractor::onMouseOver(const SDL_MouseMotionEvent& e) {}
    void BaseMouseInteractor::onDrag(const SDL_MouseMotionEvent& e) {}
    void BaseMouseInteractor::onDrop(const SDL_MouseButtonEvent& e) {}
    void BaseMouseInteractor::onClick(const SDL_MouseButtonEvent& e) {}
}
