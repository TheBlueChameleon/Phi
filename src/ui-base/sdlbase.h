#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_image.h>

namespace UiBase
{
#ifdef SDL_PRIVATE
    extern SDL_Window*   window;
    extern SDL_Renderer* renderer;
#endif

    void mainloop();
}

#endif // WINDOW_H
