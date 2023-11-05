#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL2/SDL.h>

#include "coords/coordinates.h"

namespace UiBase
{
    class Texture
    {
        private:
            SDL_Texture* texture;
            Coords::PixelCoordinates size;

            Texture(SDL_Texture* texture, Coords::PixelCoordinates size);

        public:
            Texture(int width, int height,
                    Uint32 format = SDL_PIXELFORMAT_RGBA8888,
                    int access =SDL_TEXTUREACCESS_TARGET);
            Texture(Texture& other) = default;
            Texture(Texture&& other);
            ~Texture();

            Texture& operator=(Texture&& other);

            static Texture fromFile(const std::string& path);

            SDL_Texture* expose();
            Coords::PixelCoordinates getSize() const;

            void renderAt(Coords::PixelCoordinates upperLeft) const;
    };
}

#endif // TEXTURE_H
