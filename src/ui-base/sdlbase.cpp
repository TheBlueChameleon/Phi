#include <iostream>
#include <string>
using namespace std::string_literals;

#include "base/base.h"

#define SDL_PRIVATE
#include "sdlbase.h"
#include "constants.h"

namespace UiBase
{
    SDL_Window*   window = NULL;
    SDL_Renderer* renderer = NULL;

    static void init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw SdlError("SDL could not initialize! SDL Error:\n"s + SDL_GetError());
        }

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cerr << "Warning: Linear texture filtering not enabled!";
        }

        window = SDL_CreateWindow(
                     WINDOW_TITLE,
                     SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED,
                     SCREEN_WIDTH,
                     SCREEN_HEIGHT,
                     SDL_WINDOW_SHOWN
                 );
        if (window == NULL)
        {
            throw SdlError("Window could not be created! SDL Error:\n"s + SDL_GetError());
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
        {
            throw SdlError("Renderer could not be created! SDL Error:\n"s + SDL_GetError());
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            throw SdlError("SDL_image could not initialize! SDL_image Error:\n"s + IMG_GetError());
        }
    }

    static void quit()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = NULL;
        renderer = NULL;

        //Quit SDL subsystems
        IMG_Quit();
        SDL_Quit();
    }

    void mainloop()
    {
        init();

        //Main loop flag
        bool quit_flag = false;

        //Event handler
        SDL_Event e;

        //While application is running
        while (!quit_flag)
        {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit_flag = true;
                }
            }

            //Clear screen
            SDL_RenderClear(renderer);

            //Render texture to screen
            //SDL_RenderCopy(renderer, gTexture, NULL, NULL);

            //Update screen
            SDL_RenderPresent(renderer);
        }

        quit();
    }

}
