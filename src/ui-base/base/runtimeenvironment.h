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

            void resetRenderer();

            EventDispatcher& getEventDispatcher();
            void replaceEventDispatcher(EventDispatcher* newEventDispatcher);

            //#ifdef UIBASE_PRIVATE
            std::vector<Widget*>& getWidgets();
            std::unordered_map<std::string, TTF_Font*>& getFonts();
            //#endif

            int getScreenWidth() const;
            int getScrenHeight() const;
            const char* getWindowTitle() const;

            void hideWindow();
            void showWindow();
            bool isWindowShown() const;

            void loadFont(const std::string& ID, const std::string& path, int size, const int fontStyle = TTF_STYLE_NORMAL);
            TTF_Font* getFont(const std::string& ID) const;
            TTF_Font* getFontOrThrow(const std::string& ID) const;
            bool fontExists(const std::string& ID) const;

            void mainloop();
            void render_widgets();

            Widget* findWidgetAt(Base::PixelCoordinates pos);
    };
}

#endif // RUNTIMEENVIRONMENT_H
