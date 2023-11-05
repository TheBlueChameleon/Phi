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
            SDL_Texture* texture = nullptr;
            Coords::PixelCoordinates size = {0, 0};

        public:
            Texture(SDL_Texture* texture);
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
