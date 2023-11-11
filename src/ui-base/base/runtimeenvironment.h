#ifndef RUNTIMEENVIRONMENT_H
#define RUNTIMEENVIRONMENT_H

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "base/base.h"
#include "ui-base/base/eventdispatcher.h"

namespace UiBase
{
    class Widget;

    class RuntimeEnvironment
    {
        private:
            bool initCalled = false;

            SDL_Window*   window   = nullptr;
            SDL_Renderer* renderer = nullptr;

            std::vector<Widget*> widgets;
            std::unordered_map<std::string, TTF_Font*> fonts;

            const int screenWidth  = 800;
            const int screenHeight = 600;
            const char* windowTitle = "foo bar";

            EventDispatcher* eventDispatcher = nullptr;

            RuntimeEnvironment();
            void init();

        public:
            static RuntimeEnvironment& getInstance();
            ~RuntimeEnvironment();

            RuntimeEnvironment& operator=(RuntimeEnvironment&) = delete;
            RuntimeEnvironment& operator=(RuntimeEnvironment&&) = delete;

            SDL_Window* getWindow() const;
            SDL_Renderer* getRenderer() const;

            EventDispatcher& getEventDispatcher();
            void replaceEventDispatcher(EventDispatcher* newEventDispatcher);

#ifdef UIBASE_PRIVATE
            std::vector<Widget*>& getWidgets();
            std::unordered_map<std::string, TTF_Font*>& getFonts();
#endif

            int getScreenWidth() const;
            int getScrenHeight() const;
            const char* getWindowTitle() const;

            void hideWindow();
            void showWindow();
            bool isWindowShown() const;

            void loadFont(const std::string& path, int size, const std::string& ID);

            void mainloop();
            void render_widgets();

            Widget* findWidgetAt(Base::PixelCoordinates pos);
    };
}

#endif // RUNTIMEENVIRONMENT_H
