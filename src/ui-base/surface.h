#ifndef SURFACE_H
#define SURFACE_H

#include <SDL2/SDL.h>

#include "coords/coordinates.h"

#include "texture.h"

namespace UiBase
{
    class Surface
    {
        private:
            SDL_Surface* surface = nullptr;
            Coords::PixelCoordinates size = {0, 0};

        public:
            Surface(const Coords::PixelCoordinates& size);
            Surface(SDL_Surface* surface);
            ~Surface();

            static Surface fromFile(const std::string& path);

            Texture toTexture() const;
    };
}

#endif // SURFACE_H
