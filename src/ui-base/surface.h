#ifndef SURFACE_H
#define SURFACE_H

#include <SDL2/SDL.h>

#include "base/coordinates/coordinate.h"

#include "texture.h"

namespace UiBase
{
    class Surface
    {
        private:
            SDL_Surface* surface = nullptr;
            Base::PixelCoordinates size = {0, 0};

        public:
            Surface(const Base::PixelCoordinates& size);
            Surface(SDL_Surface* surface);
            ~Surface();

            static Surface fromFile(const std::string& path);

            Texture toTexture() const;
    };
}

#endif // SURFACE_H
