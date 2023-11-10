#include "ui-base/uibase.h"

using namespace Base;
namespace UiBase
{
    void BaseMouseInteractor::startDrag(const SDL_MouseMotionEvent e)
    {
        Widget* self = dynamic_cast<Widget*>(this);

        PixelCoordinates mousePosition = {e.x, e.y};
        PixelCoordinates mouseOffset = self->getPosition() - mousePosition;

        self->makeInactive();

        substitute = new DragSubstitute(*self, mouseOffset);
        mouseButtonState = MouseButtonState::Dragged;
    }

    void BaseMouseInteractor::continueDrag(const SDL_MouseMotionEvent e)
    {
        DragSubstitute* self = dynamic_cast<DragSubstitute*>(this);

        PixelCoordinates mousePosition = {e.x, e.y};
        PixelCoordinates mouseOffset = self->getMouseOffset();

        self->setPosition(mousePosition + mouseOffset);
        mouseButtonState = MouseButtonState::Dragged;

    }

    void BaseMouseInteractor::endDrag(const SDL_MouseButtonEvent e)
    {
        DragSubstitute* self = dynamic_cast<DragSubstitute*>(this);

        Widget& original = self->getOriginal();
        BaseMouseInteractor& bmo = dynamic_cast<BaseMouseInteractor&>(original);

        delete self;
        original.makeActive();
        bmo.setMouseButtonState(MouseButtonState::Normal);
    }

    BaseMouseInteractor::MouseButtonState BaseMouseInteractor::getMouseButtonState() const
    {
        return mouseButtonState;
    }

    void BaseMouseInteractor::setMouseButtonState(MouseButtonState newMouseButtonState)
    {
        mouseButtonState = newMouseButtonState;
    }

    void BaseMouseInteractor::onMouseButton(const SDL_Event& e)
    {
        const SDL_MouseButtonEvent& eb = e.button;

        if (eb.state == SDL_PRESSED)
        {
            if (mouseButtonState == MouseButtonState::Dragged)
            {}
            else
            {
                mouseButtonState = MouseButtonState::Clicked;
                /*onClick(e);*/
            }
        }
        else if (eb.state == SDL_RELEASED)
        {
            if (mouseButtonState == MouseButtonState::Dragged)
            {
                endDrag(eb);
                /*onDrop(e);*/
            }
            else
            {
                mouseButtonState = MouseButtonState::Normal;
                /*onRelease(e);*/
            }
        }
    }

    void BaseMouseInteractor::onMouseMotion(const SDL_Event& e)
    {
        switch (mouseButtonState)
        {
            case MouseButtonState::Normal:
                //                onMouseOver(e);
                break;
            case MouseButtonState::Clicked:
                startDrag(e.motion);
                //                onDrag(e);
                break;

            case MouseButtonState::Dragged:
                continueDrag(e.motion);
                //                onDrag(e);
                break;
        }
    }

    void BaseMouseInteractor::onMouseWheel(const SDL_Event& e) {}

    const std::function<void (const SDL_Event&)>& BaseMouseInteractor::getEventHandler(const Callbacks id)
    {
        return calbacks[id];
    }

    void BaseMouseInteractor::setEventHandler(const Callbacks id, const std::function<void (const SDL_Event&)>& callback)
    {
        calbacks[id] = callback;
    }
}
