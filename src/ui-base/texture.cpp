#include <iostream>
#include <string>
using namespace std::string_literals;

#include "base/base.h"

#define SDL_PRIVATE
#include "uibase.h"

using namespace Base;

namespace UiBase
{
    Texture::Texture() :
        size(PixelCoordinates {0,0}),
        texture(nullptr)
    {}

    Texture::Texture(SDL_Texture* texture)
    {
        PixelCoordinates size;
        SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
        this->texture = texture;
        this->size = size;
    }

    Texture::Texture(const PixelCoordinates& size, int access) :
        size(size)
    {
        // TODO sanity check on size
        texture = SDL_CreateTexture(renderer,
                                    SDL_GetWindowPixelFormat(window) /*SDL_PIXELFORMAT_RGBA8888*/,
                                    access,
                                    size.x, size.y);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }

    Texture::Texture(const Texture& other) :
        Texture(other.getSize(), SDL_TEXTUREACCESS_TARGET)
    {
        // TODO handle return value = error code
        SDL_SetRenderTarget(renderer, this->texture);
        SDL_RenderCopy(renderer, other.texture, nullptr, nullptr);
        SDL_SetRenderTarget(renderer, nullptr);  // set back to screen
    }

    Texture::Texture(Texture&& other) :
        texture(other.texture),
        size(other.size)
    {
        other.texture = nullptr;
        other.size = {0,0};
    }

    Texture::~Texture()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }
        texture = nullptr;
    }

    Texture Texture::fromFile(const std::string& path)
    {
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
        {
            throw SdlError("Unable to load image '"s + path + "'\n"
                           "SDL_image Error: "s +IMG_GetError());
        }

        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
        if (newTexture == NULL)
        {
            throw SdlError("Unable to create texture from '"s + path + "'\n"
                           "SDL_image Error: "s +IMG_GetError());
        }

        return Texture(newTexture);
    }

    PixelCoordinates Texture::getSize() const
    {
        return size;
    }

    void Texture::setAlpha(Uint8 alpha)
    {
        // TODO handle return value = error code
        SDL_SetTextureAlphaMod(texture, alpha);
    }

    SDL_Texture* Texture::expose()
    {
        return texture;
    }

    void Texture::renderAt(PixelCoordinates upperLeft) const
    {
        SDL_Rect rect = {upperLeft.x, upperLeft.y, size.x, size.y};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
}
