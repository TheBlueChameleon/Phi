#include <iostream>
#include <string>
using namespace std::string_literals;

#include "base/base.h"

#define SDL_PRIVATE
#include "uibase.h"

using namespace Coords;

namespace UiBase
{
    Texture::Texture(SDL_Texture* texture, Coords::PixelCoordinates size)
    {
        this->texture = texture;
        this->size = size;
    }

    Texture::Texture(int width, int height, Uint32 format, int access)
    {
        // TODO: sanity checks
        texture = SDL_CreateTexture(renderer, format, access, width, height);
        size = {width, height};
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

    UiBase::Texture& UiBase::Texture::operator=(Texture&& other)
    {
        std::cout << "got here; self = " << texture << ", other = " << other.texture << ", " << other.size.to_string() << std::endl;

        if (texture)
        {
            SDL_DestroyTexture(texture);
        }

        texture = other.texture;
        size    = other.size;
        other.texture = nullptr;
        other.size = {0,0};

        std::cout << "got out" << std::endl;
        return *this;
    }


    Texture Texture::fromFile(const std::string& path)
    {
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
        {
            throw SdlError("Unable to load image '"s + path + "'\n"
                           "SDL_image Error: "s +IMG_GetError());
        }
        PixelCoordinates size = {loadedSurface->w, loadedSurface->h};

        //Create texture from surface pixels
        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            throw SdlError("Unable to create texture from '"s + path + "'\n"
                           "SDL_image Error: "s +IMG_GetError());
        }

        SDL_FreeSurface(loadedSurface);

        return Texture(newTexture, size);
    }

    Coords::PixelCoordinates Texture::getSize() const
    {
        return size;
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
