#include <iostream>
#include <string>
using namespace std::string_literals;

#include "base/base.h"

#define SDL_PRIVATE
#include "texture.h"
#include "sdlutil.h"

using namespace Base;
using namespace SdlUtil;

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
        if (size.x <= 0 || size.y <= 0)
        {
            throw DimensionError("Attempting to construct Texture of size " + size.to_string());
        }
        texture = SDL_CreateTexture(rte.getRenderer(),
                                    SDL_GetWindowPixelFormat(rte.getWindow()) /*SDL_PIXELFORMAT_RGBA8888*/,
                                    access,
                                    size.x, size.y);
        throwSdlErrorIfNullptr(texture, "Texture could not be created");
    }

    Texture::Texture(const Texture& other)
    {
        *this = other;
    }

    Texture::Texture(Texture&& other)
    {
        *this = std::move(other);
    }

    Texture::~Texture()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }
        texture = nullptr;
    }

    Texture& Texture::operator=(const Texture& other)
    {
        *this = Texture(other.getSize(), SDL_TEXTUREACCESS_TARGET);
        throwSdlErrorIfErrCode(SDL_SetRenderTarget(rte.getRenderer(), this->texture), "Could not set render target to texture");
        throwSdlErrorIfErrCode(SDL_RenderCopy(rte.getRenderer(), other.texture, nullptr, nullptr), "Could not copy texture");
        throwSdlErrorIfErrCode(SDL_SetRenderTarget(rte.getRenderer(), nullptr), "Could not set render target to screen");

        return *this;
    }

    Texture& Texture::operator=(Texture&& other)
    {
        size = other.size;
        texture = other.texture;

        other.size = {0, 0};
        other.texture = nullptr;

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

        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(RuntimeEnvironment::getInstance().getRenderer(), loadedSurface);
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
        throwSdlErrorIfErrCode(SDL_SetTextureAlphaMod(texture, alpha), "Could not set alpha level");
    }

    SDL_Texture* Texture::expose()
    {
        return texture;
    }

    void Texture::renderAt(PixelCoordinates upperLeft) const
    {
        SDL_Rect rect = {upperLeft.x, upperLeft.y, size.x, size.y};
        throwSdlErrorIfErrCode(SDL_RenderCopy(
                                   rte.getRenderer(), texture,
                                   NULL, &rect
                               ), "Could not render to screen");
    }
}
