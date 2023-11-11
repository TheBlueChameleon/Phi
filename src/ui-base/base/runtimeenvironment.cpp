#include <iostream>
#include <ranges>
#include <string>

using namespace std::string_literals;

#include "base/errors.h"

#define UIBASE_PRIVATE
#include "runtimeenvironment.h"
#include "ui-base/widgets/widget.h"
#include "ui-base/base/defaulteventdispatcher.h"

using namespace Base;

namespace UiBase
{
    RuntimeEnvironment::RuntimeEnvironment() {}

    void RuntimeEnvironment::init()
    {
        initCalled = true;

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            throw SdlError("SDL could not initialize! SDL Error:\n"s + SDL_GetError());
        }

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cerr << "Warning: Linear texture filtering not enabled!";
        }

        window = SDL_CreateWindow(
                     windowTitle,
                     SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED,
                     screenWidth,
                     screenHeight,
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

        eventDispatcher = new DefaultEventDispatcher();
    }

    RuntimeEnvironment& RuntimeEnvironment::getInstance()
    {
        static RuntimeEnvironment instance;

        if (!instance.initCalled)
        {
            std::cout << "call from getInstance" << std::endl;
            instance.init();
        }
        return instance;
    }

    RuntimeEnvironment::~RuntimeEnvironment()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = NULL;
        renderer = NULL;

        IMG_Quit();
        SDL_Quit();

        delete eventDispatcher;

        initCalled = false;
    }

    SDL_Window* RuntimeEnvironment::getWindow() const
    {
        return window;
    }

    SDL_Renderer* RuntimeEnvironment::getRenderer() const
    {
        return renderer;
    }

    EventDispatcher& RuntimeEnvironment::getEventDispatcher()
    {
        return *eventDispatcher;
    }

    void RuntimeEnvironment::replaceEventDispatcher(EventDispatcher* newEventDispatcher)
    {
        delete eventDispatcher;
        eventDispatcher = newEventDispatcher;
    }

    std::vector<Widget*>& RuntimeEnvironment::getWidgets()
    {
        return widgets;
    }

    std::unordered_map<std::string, TTF_Font*>& RuntimeEnvironment::getFonts()
    {
        return fonts;
    }

    int RuntimeEnvironment::getScreenWidth() const
    {
        return screenWidth;
    }

    int RuntimeEnvironment::getScrenHeight() const
    {
        return screenHeight;
    }

    const char* RuntimeEnvironment::getWindowTitle() const
    {
        return windowTitle;
    }

    void RuntimeEnvironment::loadFont(const std::string& path, int size, const std::string& ID)
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

    void RuntimeEnvironment::mainloop()
    {
        do
        {
            SDL_RenderClear(renderer);
            render_widgets();
            SDL_RenderPresent(renderer);
        }
        while (eventDispatcher->dispatchEvents());
    }

    void RuntimeEnvironment::render_widgets()
    {
        for (auto widget : std::ranges::filter_view(widgets, &Widget::isVisible))
        {
            (*widget)
            .render()
            .renderAt(widget->getPosition());
        }
    }

    Widget* RuntimeEnvironment::findWidgetAt(Base::PixelCoordinates pos)
    {
        for (auto widget : std::views::reverse(widgets) | std::views::filter(&Widget::isVisible) | std::views::filter(&Widget::isActive))
        {
            PixelCoordinates upperLeft = widget->getPosition();
            PixelCoordinates lowerRight = upperLeft + widget->getSize() - PixelCoordinates {1, 1};
            if (isWithin(pos, upperLeft, lowerRight))
            {
                return widget;
            }
        }

        return nullptr;
    }
}