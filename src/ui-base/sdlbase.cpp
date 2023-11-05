#include <iostream>
#include <string>
using namespace std::string_literals;

#include "base/base.h"

#define SDL_PRIVATE
#define UIBASE_PRIVATE
#include "uibase.h"
#include "ui-base/widgets/basetexturebutton.h"

namespace UiBase
{
    static void init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
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
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

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

        Texture t = Texture::fromFile("res/22-html-table_2.png");
        BaseTextureButton b = BaseTextureButton::fromFile(Coords::PixelCoordinates{150,50}, "res/22-html-divpspan.png");

        SDL_Event e;

        do
        {
            SDL_RenderClear(renderer);

            //Render texture to screen
            t.renderAt({50,50});
            t.renderAt({60,60});
            b.render();

            SDL_RenderPresent(renderer);
        }
        while (dispatch_events(e));

        quit();
    }

    bool dispatch_events(SDL_Event& e)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                return false;
            }
        }

        return true;
    }

    void render_widgets()
    {
        for (auto widgetRef : widgets)
        {
            auto& widget = widgetRef.get();

        }
    }
}
