#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <unordered_map>

#include "ui-base/widgets/widget.h"

namespace UiBase
{
    class BaseWidget :
        public RuntimeEnvironmentUser,
        public Widget
    {
        private:
            bool visible = true;
            bool active = true;
            bool dragDropCapable = false;

            bool mouseOver = false;
            bool clicked = false;

            Base::PixelCoordinates position;
            Base::PixelCoordinates size;
            std::unordered_map<Callbacks, std::function<void(const SDL_Event&)>> callbacks;

            void invokeOptionalCallback(const Callbacks id, const SDL_Event& event);

        public:
            BaseWidget(const Base::PixelCoordinates& position, const Base::PixelCoordinates& size);
            ~BaseWidget();

            // Widget interface
            bool isVisible() const;
            void makeVisible();
            void makeInvisible();

            bool isActive() const;
            void makeActive();
            void makeInactive();

            bool isDragDropCapable() const;
            void makeDragDropCapable();
            void makeDragDropIncapable();

            bool hasMouseOver() const;
            bool isClicked() const;

            Base::PixelCoordinates getPosition() const;
            void setPosition(const Base::PixelCoordinates& pos);
            Base::PixelCoordinates getSize() const;
            void setSize(const Base::PixelCoordinates& size);

            // TODO: virtual?
            void onMouseButton(const SDL_Event& e);
            void onLostFocus(const SDL_Event& e);
            void onGainFocus(const SDL_Event& e);
            void onMouseMotion(const SDL_Event& e);
            void onLostMouseOver(const SDL_Event& e);
            void onGainMouseOver(const SDL_Event& e);
            void onDrag(const SDL_Event& e);
            void onDrop(const SDL_Event& e);
            void onMouseWheel(const SDL_Event& e);

            const std::function<void(const SDL_Event&)>& getEventHandler(const Callbacks id);
            void setEventHandler(const Callbacks id, const std::function<void(const SDL_Event&)>& callback);
    };
}

#endif // BASEWIDGET_H
