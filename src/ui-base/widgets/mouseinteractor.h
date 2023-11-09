#ifndef MOUSEINTERACTOR_H
#define MOUSEINTERACTOR_H

#include <functional>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "callbacks.h"

namespace UiBase
{
    struct MouseInteractor
    {
        virtual void onMouseButton(const SDL_Event& e) = 0;
        virtual void onMouseMotion(const SDL_Event& e) = 0;
        virtual void onMouseWheel(const SDL_Event& e) = 0;

        virtual const std::function<void(const SDL_Event&)>& getEventHandler(const Callbacks id) = 0;
        virtual void setEventHandler(const Callbacks id, const std::function<void(const SDL_Event&)>& callback) = 0;
    };
}
#endif // MOUSEINTERACTOR_H
