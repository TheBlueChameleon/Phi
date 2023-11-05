#define SDL_PRIVATE
#define UIBASE_PRIVATE
#include "globals.h"

namespace UiBase
{
    SDL_Window*   window = NULL;
    SDL_Renderer* renderer = NULL;

    std::vector<Widget*> widgets;

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "foo bar";
}
