#ifndef MOUSEINTERACTOR_H
#define MOUSEINTERACTOR_H

#include <SDL.h>

namespace UiBase
{
    struct MouseInteractor
    {
        virtual void onMouseButton(const SDL_MouseButtonEvent& e) = 0;
        virtual void onMouseOver(const SDL_MouseMotionEvent& e) = 0;
        virtual void onMouseWheel(const SDL_MouseWheelEvent& e) = 0;

        virtual void onClick(const SDL_MouseButtonEvent& e) = 0;
    };
}
#endif // MOUSEINTERACTOR_H
