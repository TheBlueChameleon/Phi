#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

namespace UiBase
{
    enum class EventDispatcherMode
    {
        Normal, DragAndDrop
    };

    class Widget;

    struct EventDispatcher
    {
        virtual ~EventDispatcher() = default;

        virtual bool dispatchEvents() = 0;

        virtual EventDispatcherMode getMode() const = 0;
        virtual void setMode(EventDispatcherMode mode, Widget* target) = 0;
    };
}

#endif // EVENTDISPATCHER_H
