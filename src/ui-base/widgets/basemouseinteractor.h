#ifndef BASEMOUSEINTERACTOR_H
#define BASEMOUSEINTERACTOR_H

#include "mouseinteractor.h"

namespace UiBase
{
    class DragSubstitute;

    class BaseMouseInteractor :
        public MouseInteractor
    {
        public:
            enum class MouseButtonState
            {
                Normal,
                Clicked,
                Dragged
            };

        private:
            MouseButtonState mouseButtonState = MouseButtonState::Normal;
            std::map<Callbacks, std::function<void(const SDL_Event&)>> calbacks;
            DragSubstitute* substitute = nullptr;

            void startDrag(const SDL_MouseMotionEvent e);
            void continueDrag(const SDL_MouseMotionEvent e);
            void endDrag(const SDL_MouseButtonEvent e);

        public:
            BaseMouseInteractor() = default;

            MouseButtonState getMouseButtonState() const;
            void setMouseButtonState(MouseButtonState newMouseButtonState);

            // MouseInteractor interface
            virtual void onMouseButton(const SDL_Event& e);
            virtual void onMouseMotion(const SDL_Event& e);
            virtual void onMouseWheel(const SDL_Event& e);

            const std::function<void (const SDL_Event&)>& getEventHandler(const Callbacks id);
            void setEventHandler(const Callbacks id, const std::function<void (const SDL_Event&)>& callback);

    };
}

#endif // BASEMOUSEINTERACTOR_H
