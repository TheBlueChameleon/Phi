#define SDL_PRIVATE
#define UIBASE_PRIVATE
#include "globals.h"

namespace UiBase
{
    // SDL PRIVATE
    SDL_Window*   window = NULL;
    SDL_Renderer* renderer = NULL;

    // UiBase PRIVATE
    std::vector<Widget*> widgets;
    std::unordered_map<std::string, TTF_Font*> fonts;

    // PUBLIC
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "foo bar";
}
