#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

namespace UiBase
{
    void mainloop();
    bool dispatch_events(SDL_Event& e);
}

#endif // WINDOW_H
