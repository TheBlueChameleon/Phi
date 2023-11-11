#ifndef SURFACE_H
#define SURFACE_H

#include <SDL2/SDL.h>

#include "base/coordinates/coordinate.h"
#include "ui-base/base/sdlutil.h"
#include "texture.h"

namespace UiBase
{
    class Surface : RuntimeEnvironmentUser
    {
        private:
            SDL_Surface* surface = nullptr;
            Base::PixelCoordinates size = {0, 0};

        public:
            Surface() = default;
            Surface(SDL_Surface* surface);
            Surface(const Base::PixelCoordinates& size, Uint32 color = 0xFFFFFFFF);
            Surface(const Surface& other);
            Surface(Surface&& other);
            ~Surface();

            Surface& operator=(const Surface& other);
            Surface& operator=(Surface&& other);

            static Surface fromFile(const std::string& path);
            static Surface fromText(const std::string& text, const std::string& fontID, const SDL_Color fontColor = SdlColors::black, Uint32 wrapLength = 0);

            SDL_Surface* expose();
            Base::PixelCoordinates getSize() const;

            Uint32& pixelAt(int x, int y);
            void fillWith(Uint32 color);

            Texture toTexture(int access = SDL_TEXTUREACCESS_TARGET) const;
    };
}

#endif // SURFACE_H
