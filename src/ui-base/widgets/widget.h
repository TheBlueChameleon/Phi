#ifndef WIDGET_H
#define WIDGET_H

#include <functional>

#include "base/coordinates/coordinate.h"

#include "ui-base/base/callbacks.h"
#include "ui-base/base/texture.h"

namespace UiBase
{
    struct Widget
    {
        virtual ~Widget() = default;

        virtual bool isVisible() const = 0;
        virtual void makeVisible() = 0;
        virtual void makeInvisible() = 0;

        virtual bool isActive() const = 0;
        virtual void makeActive() = 0;
        virtual void makeInactive() = 0;

        virtual bool isDragDropCapable() const = 0;
        virtual void makeDragDropCapable() = 0;
        virtual void makeDragDropIncapable() = 0;

        virtual void onMouseButton(const SDL_Event& e) = 0;
        virtual void onLostFocus(const SDL_Event& e) = 0;
        virtual void onGainFocus(const SDL_Event& e) = 0;
        virtual void onMouseMotion(const SDL_Event& e) = 0;
        virtual void onLostMouseOver(const SDL_Event& e) = 0;
        virtual void onGainMouseOver(const SDL_Event& e) = 0;
        virtual void onMouseWheel(const SDL_Event& e) = 0;

        virtual const std::function<void(const SDL_Event&)>& getEventHandler(const Callbacks id) = 0;
        virtual void setEventHandler(const Callbacks id, const std::function<void(const SDL_Event&)>& callback) = 0;

        virtual Base::PixelCoordinates getPosition() const = 0;
        virtual void setPosition(const Base::PixelCoordinates& pos) = 0;
        virtual Base::PixelCoordinates getSize() const = 0;
        virtual void setSize(const Base::PixelCoordinates& pos) = 0;

        virtual const Texture& render() const = 0;
    };
}

#endif // WIDGET_H
