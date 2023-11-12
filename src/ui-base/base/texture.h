#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL2/SDL.h>

#include "base/coordinates/coordinate.h"

#include "runtimeenvironmentuser.h"
#include "ui-base/base/sdlutil.h"

namespace UiBase
{
    class Texture : RuntimeEnvironmentUser
    {
        private:
            SDL_Texture* texture = nullptr;
            Base::PixelCoordinates size = {0, 0};

        public:
            Texture() = default;
            Texture(SDL_Texture* texture);
            Texture(const Base::PixelCoordinates& size, int access = SDL_TEXTUREACCESS_TARGET, const SDL_Color& color = SdlColors::transparent);
            Texture(const Texture& other);
            Texture(Texture&& other);
            ~Texture();

            Texture& operator=(const Texture& other);
            Texture& operator=(Texture&& other);

            static Texture fromFile(const std::string& path);

            SDL_Texture* expose();
            Base::PixelCoordinates getSize() const;

            void setAlpha(Uint8 alpha);

            void renderAt(Base::PixelCoordinates upperLeft) const;
            void renderOnto(Texture& target, Base::PixelCoordinates upperLeft) const;
            void renderOntoCentered(Texture& target) const;
    };
}

#endif // TEXTURE_H
