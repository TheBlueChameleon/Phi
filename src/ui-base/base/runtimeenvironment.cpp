#include <iostream>
#include <ranges>
#include <string>

#include "base/errors.h"

#define UIBASE_PRIVATE
#include "runtimeenvironment.h"
#include "ui-base/base/sdlutil.h"
#include "ui-base/widgets/widget.h"
#include "ui-base/base/defaulteventdispatcher.h"

// TODO remove debug stuff
#include "ui-base/base/surface.h"
#include <ui-base/widgets/impl/texturelabel.h>
#include "ui-base/widgets/impl/texturebutton.h"

using namespace Base;
using namespace SdlUtil;

namespace UiBase
{
    RuntimeEnvironment::RuntimeEnvironment() {}

    void RuntimeEnvironment::init()
    {
        initCalled = true;

        throwSdlErrorIfErrCode(SDL_Init(SDL_INIT_EVERYTHING), "SDL could not be initialized!");

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
                     SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
                 );
        throwSdlErrorIfNullptr(window, "Window could not be created!");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
        throwSdlErrorIfNullptr(renderer, "Renderer could not be created!");
        resetRenderer();

        int imgFlags = IMG_INIT_PNG;
        throwSdlErrorIfErrCode(!(IMG_Init(imgFlags) & imgFlags), "SDL_image could not be initialized!");

        throwSdlErrorIfErrCode(TTF_Init(), "SDL_ttf could not be initialized!");

        eventDispatcher = new DefaultEventDispatcher();
    }

    RuntimeEnvironment& RuntimeEnvironment::getInstance()
    {
        static RuntimeEnvironment instance;

        if (!instance.initCalled)
        {
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

    void RuntimeEnvironment::resetRenderer()
    {
        throwSdlErrorIfErrCode(SDL_SetRenderTarget(renderer, nullptr), "Could not set render target to screen");
        throwSdlErrorIfErrCode(SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF), "Could not set draw color");
        throwSdlErrorIfErrCode(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND), "Could not set blend mode");
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

    void RuntimeEnvironment::hideWindow()
    {
        SDL_HideWindow(window);
    }

    void RuntimeEnvironment::showWindow()
    {
        SDL_ShowWindow(window);
    }

    bool RuntimeEnvironment::isWindowShown() const
    {
        return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
    }

    void RuntimeEnvironment::loadFont(const std::string& ID, const std::string& path, int size, const int fontStyle)
    {
        if (fonts.contains(ID))
        {
            throw Base::KeyError("Font ID '" + ID + "' is already in use");
        }

        auto fontPtr = TTF_OpenFont(path.c_str(), size);
        if (!fontPtr)
        {
            throw SdlError("Could not load font '" + path + "'");
        }

        if (fontStyle != TTF_STYLE_NORMAL)
        {
            TTF_SetFontStyle(fontPtr, fontStyle);
        }

        auto [it, success] = fonts.emplace(ID, fontPtr);
        if (!success)
        {
            TTF_CloseFont(fontPtr);
            throw Base::MemoryManagementError("FontMap could not be updated");
        }
    }

    TTF_Font* RuntimeEnvironment::getFont(const std::string& ID) const
    {
        // fonts[ID] would implicitly construct a new element if no key ID exists, thus this walkaround

        auto fontIterator = fonts.find(ID);
        if (fontIterator == fonts.end())
        {
            return nullptr;
        }
        else
        {
            return fontIterator->second;
        }
    }

    TTF_Font* RuntimeEnvironment::getFontOrThrow(const std::string& ID) const
    {
        auto fontIterator = fonts.find(ID);
        if (fontIterator == fonts.end())
        {
            throw KeyError("No font with key '" + ID + "' was registered");
        }
        else
        {
            return fontIterator->second;
        }
    }

    bool RuntimeEnvironment::fontExists(const std::string& ID) const
    {
        return fonts.contains(ID);
    }

    void RuntimeEnvironment::mainloop()
    {
        do
        {
            resetRenderer();
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
