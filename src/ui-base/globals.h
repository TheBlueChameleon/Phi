#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <functional>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "widgets/widget.h"

namespace UiBase
{
#ifdef SDL_PRIVATE
    extern SDL_Window*   window;
    extern SDL_Renderer* renderer;
#endif

#ifdef UIBASE_PRIVATE
    extern std::vector<Widget*> widgets;
#endif

    extern const int SCREEN_WIDTH;
    extern const int SCREEN_HEIGHT;
    extern const char* WINDOW_TITLE;
}

#endif // CONSTANTS_H
