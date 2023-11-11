#ifndef DEFAULTEVENTDISPATCHER_H
#define DEFAULTEVENTDISPATCHER_H

#include <concepts>

#include <SDL2/SDL.h>

#include "ui-base/base/eventdispatcher.h"
#include "ui-base/widgets/widget.h"

namespace UiBase
{
    namespace EventDispatcherTypes
    {
        using WidgetMethod = void (Widget::*)(const SDL_Event&);

        using MotionOffset = decltype(&SDL_Event::motion);
        using ButtonOffset = decltype(&SDL_Event::button);
        using WheelOffset = decltype(&SDL_Event::wheel);

        template<typename T>
        concept MouseEventOffset =
            std::is_convertible_v<T, EventDispatcherTypes::MotionOffset> ||
            std::is_convertible_v<T, EventDispatcherTypes::ButtonOffset> ||
            std::is_convertible_v<T, EventDispatcherTypes::WheelOffset>;
    }

    class DefaultEventDispatcher :
        public RuntimeEnvironmentUser,
        public EventDispatcher
    {
        private:
            EventDispatcherMode mode = EventDispatcherMode::Normal;
            Widget* modeTarget = nullptr;
            Widget* lastClicked = nullptr;
            Widget* lastTouched = nullptr;
            Widget* focussed = nullptr;

        public:
            DefaultEventDispatcher() = default;

            // EventDispatcher interface
            bool dispatchEvents();

            EventDispatcherMode getMode() const;
            void setMode(EventDispatcherMode newMode, Widget* newTarget);
            void restoreNormalMode(const SDL_Event& e);

            // local extension
            bool dispatchNormalMode(const SDL_Event& e);

            Widget* dispatchMouseEvent(const SDL_Event& e, EventDispatcherTypes::WidgetMethod method, EventDispatcherTypes::MouseEventOffset auto offset);
            void dispatchUpdateLastTouched(Widget* currentlyTouched, const SDL_Event& e);
            void dispatchUpdateFocus(Widget* currentlyFocussed, const SDL_Event& e);

            bool dispatchDragAndDropMode(const SDL_Event& e);

            void dispatchDragAndDropMotion(const SDL_Event& e);
            void enterDragAndDropMode(const SDL_Event& e, Widget* draggedWidget);
            void leaveDragAndDropMode(const SDL_Event& e);
    };
}

#endif // DEFAULTEVENTDISPATCHER_H
