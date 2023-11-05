#ifndef BASEMOUSEINTERACTOR_H
#define BASEMOUSEINTERACTOR_H

#include "mouseinteractor.h"

namespace UiBase
{
    class BaseMouseInteractor : public MouseInteractor
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

        public:
            BaseMouseInteractor() = default;

            MouseButtonState getMouseButtonState() const;

            // MouseInteractor interface
            virtual void onMouseButton(const SDL_MouseButtonEvent& e);
            virtual void onMouseMotion(const SDL_MouseMotionEvent& e);
            virtual void onMouseWheel(const SDL_MouseWheelEvent& e);

            virtual void onMouseOver(const SDL_MouseMotionEvent& e);
            virtual void onDrag(const SDL_MouseMotionEvent& e);
            virtual void onDrop(const SDL_MouseButtonEvent& e);
            virtual void onClick(const SDL_MouseButtonEvent& e);
    };
}

#endif // BASEMOUSEINTERACTOR_H
