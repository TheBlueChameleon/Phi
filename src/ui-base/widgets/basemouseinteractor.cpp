#include "ui-base/uibase.h"
#include <iostream>

namespace UiBase
{
    void BaseMouseInteractor::startDrag(const SDL_MouseMotionEvent e)
    {
        Widget* self = dynamic_cast<Widget*>(this);
        std::cout << "MM on " << this << "/" << self << std::endl;
        std::cout << "drag start" << std::endl;

        Coords::PixelCoordinates mousePosition = {e.x, e.y};
        Coords::PixelCoordinates mouseOffset = self->getPosition() - mousePosition;
        std::cout << "  MO = " << mouseOffset.to_string() << " for " << self << std::endl;

        self->makeInactive();

        substitute = new DragSubstitute(*self, mouseOffset);
        mouseButtonState = MouseButtonState::Dragged;
    }

    void BaseMouseInteractor::continueDrag(const SDL_MouseMotionEvent e)
    {
        DragSubstitute* self = dynamic_cast<DragSubstitute*>(this);

        std::cout << "MM on " << this << "/" << self <<  std::endl;
        std::cout << "drag cont" << std::endl;

        Coords::PixelCoordinates mousePosition = {e.x, e.y};
        Coords::PixelCoordinates mouseOffset = self->getMouseOffset();

        self->setPosition(mousePosition + mouseOffset);
        mouseButtonState = MouseButtonState::Dragged;

    }

    void BaseMouseInteractor::endDrag(const SDL_MouseButtonEvent e)
    {
        DragSubstitute* self = dynamic_cast<DragSubstitute*>(this);
        std::cout << "MM on " << this << "/" << self <<  std::endl;
        std::cout << "drag end" << std::endl;

        Widget& original = self->getOriginal();
        BaseMouseInteractor& bmo = dynamic_cast<BaseMouseInteractor&>(original);

        delete self;
        original.makeActive();
        bmo.setMouseButtonState(MouseButtonState::Normal);

        std::cout << "cast ok"<< std::endl;
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
            std::cout << "released " << this << std::endl;
            if (mouseButtonState == MouseButtonState::Dragged)
            {
                std::cout << "  from drag" << std::endl;
                endDrag(eb);
                /*onDrop(e);*/
            }
            else
            {
                std::cout << "  from click" << std::endl;
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
                std::cout << "MM:NORM" << std::endl;
                //                onMouseOver(e);
                break;
            case MouseButtonState::Clicked:
                std::cout << "MM:CLICK" << std::endl;
                startDrag(e.motion);
                //                onDrag(e);
                break;

            case MouseButtonState::Dragged:
                std::cout << "MM:DRAG" << std::endl;
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
