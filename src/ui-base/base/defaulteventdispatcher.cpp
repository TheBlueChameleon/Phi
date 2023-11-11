#include <iostream>

#include "defaulteventdispatcher.h"
#include "ui-base/widgets/dragsubstitute.h"

#include <SDL2/SDL.h>

#include <string>
using namespace std::string_literals;

using namespace Base;

namespace UiBase
{
    bool DefaultEventDispatcher::dispatchEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            switch (mode)
            {
                case EventDispatcherMode::Normal:
                    return dispatchNormalMode(e);
                case EventDispatcherMode::DragAndDrop:
                    return dispatchDragAndDropMode(e);
                default:
                    throw std::runtime_error("invalid mode in dispatch_events: "s + std::to_string(static_cast<int>(mode)));
            }
        }

        return true;
    }

    EventDispatcherMode DefaultEventDispatcher::getMode() const
    {
        return mode;
    }

    void DefaultEventDispatcher::setMode(EventDispatcherMode newMode, Widget* newTarget)
    {
        mode = newMode;
        modeTarget = newTarget;
        std::cout << "mode: " << static_cast<int>(mode) << std::endl;
    }

    void DefaultEventDispatcher::restoreNormalMode(const SDL_Event& e)
    {
        lastClicked = nullptr;
        lastTouched = nullptr;
        setMode(EventDispatcherMode::Normal, nullptr);
    }

    bool DefaultEventDispatcher::dispatchNormalMode(const SDL_Event& e)
    {
        switch (e.type)
        {
            case SDL_MOUSEMOTION:
                if (lastClicked)
                {
                    enterDragAndDropMode(e, lastClicked);
                }
                else
                {
                    Widget* currentlyTouched = dispatchMouseEvent(e, &Widget::onMouseMotion, &SDL_Event::motion);
                    dispatchUpdateLastTouched(currentlyTouched, e);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                lastClicked = dispatchMouseEvent(e, &Widget::onMouseButton, &SDL_Event::motion);
                dispatchUpdateFocus(lastClicked, e);
                if (lastClicked && !lastClicked->isDragDropCapable())
                {
                    lastClicked = nullptr;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                dispatchMouseEvent(e, &Widget::onMouseButton, &SDL_Event::motion);
                lastClicked =  nullptr;
                break;

            case SDL_MOUSEWHEEL:
                dispatchMouseEvent(e, &Widget::onMouseWheel, &SDL_Event::motion);
                break;

            case SDL_QUIT:
            case SDL_APP_TERMINATING:
                return false;
        }

        return true;
    }

    Widget* DefaultEventDispatcher::dispatchMouseEvent(const SDL_Event& e, EventDispatcherTypes::WidgetMethod method, EventDispatcherTypes::MouseEventOffset auto offset)
    {
        const decltype(e.*offset)& concreteEvent = e.*offset;
        const PixelCoordinates pos = {concreteEvent.x, concreteEvent.y};
        Widget* widget = rte.findWidgetAt(pos);
        if (widget)
        {
            (widget->*method)(e);
        }
        return widget;
    }

    void DefaultEventDispatcher::dispatchUpdateLastTouched(Widget* currentlyTouched, const SDL_Event& e)
    {
        if (currentlyTouched != lastTouched)
        {
            if (lastTouched)
            {
                lastTouched->onLostMouseOver(e);
            }

            if (currentlyTouched)
            {
                currentlyTouched->onGainMouseOver(e);
            }

            lastTouched = currentlyTouched;
        }
    }

    void DefaultEventDispatcher::dispatchUpdateFocus(Widget* currentlyFocussed, const SDL_Event& e)
    {
        if (currentlyFocussed && currentlyFocussed != focussed)
        {
            if (focussed)
            {
                lastTouched->onLostFocus(e);
            }

            currentlyFocussed->onGainFocus(e);
            focussed = currentlyFocussed;
        }
    }

    bool DefaultEventDispatcher::dispatchDragAndDropMode(const SDL_Event& e)
    {
        switch (e.type)
        {
            case SDL_MOUSEMOTION:
                dispatchDragAndDropMotion(e);
                return true;

            case SDL_WINDOWEVENT:
            case SDL_MOUSEBUTTONUP:
                leaveDragAndDropMode(e);
                return true;

            case SDL_QUIT:
            case SDL_APP_TERMINATING:
                return false;
        }

        return true;
    }

    void DefaultEventDispatcher::dispatchDragAndDropMotion(const SDL_Event& e)
    {
        DragSubstitute* substitute = dynamic_cast<DragSubstitute*>(modeTarget);
        if (!substitute)
        {
            throw std::runtime_error("Attempting to drag a non-DragSubstitute");
        }

        const SDL_MouseMotionEvent em = e.motion;
        PixelCoordinates mousePosition = {em.x, em.y};
        PixelCoordinates mouseOffset = substitute->getMouseOffset();

        substitute->setPosition(mousePosition + mouseOffset);
        substitute->render();
    }

    void DefaultEventDispatcher::enterDragAndDropMode(const SDL_Event& e, Widget* draggedWidget)
    {
        // TODO: original.onBeginDragAndDrop(e);

        const auto& em = e.motion;
        PixelCoordinates mousePosition = {em.x, em.y};
        PixelCoordinates mouseOffset = draggedWidget->getPosition() - mousePosition;

        Widget* substitute = new DragSubstitute(*draggedWidget, mouseOffset);
        setMode(EventDispatcherMode::DragAndDrop, substitute);
    }

    void DefaultEventDispatcher::leaveDragAndDropMode(const SDL_Event& e)
    {
        DragSubstitute* substitutePtr = dynamic_cast<DragSubstitute*>(modeTarget);
        if (substitutePtr)
        {
            Widget& original = substitutePtr->getOriginal();
            original.onLostMouseOver(e);
            // TODO: original.onEndDragAndDrop(e);
        }
        delete modeTarget;
        restoreNormalMode(e);
    }
}
