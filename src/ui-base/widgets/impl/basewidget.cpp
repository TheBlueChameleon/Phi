#include <algorithm>
#include <iostream>

#define UIBASE_PRIVATE
#include "basewidget.h"
#include "ui-base/base/runtimeenvironment.h"
#include "ui-base/base/callbacks.h"

using namespace Base;
namespace UiBase
{
    void BaseWidget::invokeOptionalCallback(const Callbacks id, const SDL_Event& event)
    {
        const auto callback = callbacks[id];
        if (callback)
        {
            callback(event);
        }
    }

    BaseWidget::BaseWidget(const PixelCoordinates& position, const PixelCoordinates& size) :
        position(position), size(size)
    {
        rte.getWidgets().push_back(this);
    }

    BaseWidget::~BaseWidget()
    {
        auto it = std::find(rte.getWidgets().begin(), rte.getWidgets().end(), this);
        rte.getWidgets().erase(it);
    }

    bool BaseWidget::isVisible() const
    {
        return visible;
    }

    void BaseWidget::makeVisible()
    {
        visible = true;
    }

    void BaseWidget::makeInvisible()
    {
        visible = false;
    }

    bool BaseWidget::isActive() const
    {
        return active;
    }

    void BaseWidget::makeActive()
    {
        active = true;
    }

    void BaseWidget::makeInactive()
    {
        active = false;
    }

    bool BaseWidget::isDragDropCapable() const
    {
        return dragDropCapable;
    }

    void BaseWidget::makeDragDropCapable()
    {
        dragDropCapable = true;
    }

    void BaseWidget::makeDragDropIncapable()
    {
        dragDropCapable = false;
    }

    bool BaseWidget::hasMouseOver() const
    {
        return mouseOver;
    }

    bool BaseWidget::isClicked() const
    {
        return clicked;
    }

    PixelCoordinates BaseWidget::getPosition() const
    {
        return position;
    }

    void BaseWidget::setPosition(const PixelCoordinates& pos)
    {
        position = pos;
    }

    PixelCoordinates BaseWidget::getSize() const
    {
        return size;
    }

    void BaseWidget::setSize(const PixelCoordinates& newSize)
    {
        size = newSize;
    }

    void BaseWidget::onMouseButton(const SDL_Event& e)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            clicked = true;
        }

        if (e.type == SDL_MOUSEBUTTONUP)
        {
            if (clicked)
            {
                invokeOptionalCallback(Callbacks::Clicked, e);
            }
            clicked = false;
        }
    }

    void BaseWidget::onLostFocus(const SDL_Event& e)
    {
        std::cout << "lost focus: " << this << std::endl;
    }

    void BaseWidget::onGainFocus(const SDL_Event& e)
    {
        std::cout << "got focus: " << this << std::endl;
    }

    void BaseWidget::onMouseMotion(const SDL_Event& e) {}

    void BaseWidget::onLostMouseOver(const SDL_Event& e)
    {
        mouseOver = false;
        clicked = false;
    }

    void BaseWidget::onGainMouseOver(const SDL_Event& e)
    {
        mouseOver = true;
    }

    void BaseWidget::onMouseWheel(const SDL_Event& e)
    {

    }

    const std::function<void (const SDL_Event&)>& BaseWidget::getEventHandler(const Callbacks id)
    {
        return callbacks[id];
    }

    void BaseWidget::setEventHandler(const Callbacks id, const std::function<void (const SDL_Event&)>& callback)
    {
        callbacks[id] = callback;
    }
}
