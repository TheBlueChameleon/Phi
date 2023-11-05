#include <cstdlib>
#include <concepts>
#include <iostream>
#include <string>
using namespace std::string_literals;
#include <ranges>

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "base/base.h"
#include "coords/coordinates.h"

#define SDL_PRIVATE
#define UIBASE_PRIVATE
#include "uibase.h"
#include "ui-base/widgets/texturebutton.h"

namespace UiBase
{
    template<typename T>
    concept MouseEvent =
        std::is_convertible_v<T, SDL_MouseButtonEvent> ||
        std::is_convertible_v<T, SDL_MouseMotionEvent> ||
        std::is_convertible_v<T, SDL_MouseWheelEvent>;

    template<MouseEvent E>
    using MIMethod = void (MouseInteractor::*)(const E&);

    template<MouseEvent E> void dispatch_mouseEvent(E& e, MIMethod<E> method);

    // ====================================================================== //

    void initUI(bool autoCallQuitUI)
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

        if (autoCallQuitUI)
        {
            std::atexit(quitUI);
        }
    }

    void loadFont(const std::string& path, int size, const std::string& ID)
    {
        if (fonts.contains(ID))
        {
            throw Base::KeyError("Font ID '" + ID + "' is already in use");
        }

        auto fontPtr = TTF_OpenFont(path.c_str(), size);

        if (!fontPtr)
        {
            throw SdlError("Could not load font '"s + path + "'");
        }

        auto [it, success] = fonts.emplace(ID, fontPtr);

        if (!success)
        {
            TTF_CloseFont(fontPtr);
            throw Base::MemoryManagementError("FontMap could not be updated");
        }
    }

    void quitUI()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = NULL;
        renderer = NULL;

        IMG_Quit();
        SDL_Quit();
    }

    void uiMainloop()
    {
        do
        {
            SDL_RenderClear(renderer);
            render_widgets();
            SDL_RenderPresent(renderer);
        }
        while (dispatch_events());
    }

    void render_widgets()
    {
        for (auto widget : widgets)
        {
            if (widget->isVisible())
            {
                widget->render();
            }
        }
    }

    bool dispatch_events()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
                case SDL_MOUSEMOTION:
                    dispatch_mouseEvent(e.motion, &MouseInteractor::onMouseMotion);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    dispatch_mouseEvent(e.button, &MouseInteractor::onMouseButton);
                    break;

                case SDL_MOUSEWHEEL:
                    dispatch_mouseEvent(e.wheel, &MouseInteractor::onMouseWheel);
                    break;

                case SDL_QUIT:
                    return false;
            }
        }

        return true;
    }

    template<MouseEvent E>
    void dispatch_mouseEvent(E& e, MIMethod<E> method)
    {
        Coords::PixelCoordinates pos = {e.x, e.y};
        Widget* widget = findWidgetAt(pos);
        MouseInteractor* miWidget = dynamic_cast<MouseInteractor*>(widget);
        if (miWidget)
        {
            (miWidget->*method)(e);
        }
    }

    Widget* findWidgetAt(Coords::PixelCoordinates pos)
    {
        for (auto widget :  std::views::reverse(widgets))
        {
            Coords::PixelCoordinates upperLeft = widget->getPosition();
            Coords::PixelCoordinates lowerRight = upperLeft + widget->getSize() - Coords::PixelCoordinates {1, 1};
            if (Coords::isWithin(pos, upperLeft, lowerRight))
            {
                return widget;
            }
        }

        return nullptr;
    }
}
