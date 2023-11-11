#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "base/errors.h"

#include "surface.h"
#include "sdlutil.h"

using namespace Base;
using namespace SdlUtil;

namespace UiBase
{
    Surface::Surface(SDL_Surface* surface) :
        surface(surface),
        size({surface->w, surface->h})
    {}

    Surface::Surface(const PixelCoordinates& size, Uint32 color) :
        size(size)
    {
        if (size.x <= 0 || size.y <= 0)
        {
            throw DimensionError("Attempting to construct Surface of size " + size.to_string());
        }

        //(Uint32 flags, int width, int height, int depth, Uint32 format);
        surface = SDL_CreateRGBSurfaceWithFormat(
                      0,
                      size.x, size.y, 32,
                      SDL_GetWindowSurface(rte.getWindow())->format->format
                  );
        throwSdlErrorIfNullptr(surface, "Could not create surface");

        if (color)
        {
            fillWith(color);
        }
    }

    Surface::Surface(const Surface& other)
    {
        *this = other;
    }

    Surface::Surface(Surface&& other)
    {
        *this = std::move(other);
    }

    Surface::~Surface()
    {
        if (surface)
        {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }

    Surface& Surface::operator=(const Surface& other)
    {
        *this = Surface(other.size);
        SDL_Rect nullRect = {0,0,0,0};
        throwSdlErrorIfErrCode(SDL_BlitSurface(other.surface, nullptr, this->surface, &nullRect), "Could not copy surface");
        return *this;
    }

    Surface& Surface::operator=(Surface&& other)
    {
        surface = other.surface;
        size = other.size;

        other.surface = nullptr;
        other.size = {0,0};

        return *this;
    }

    Surface Surface::fromFile(const std::string& path)
    {
        SDL_Surface* surface = IMG_Load(path.c_str());
        throwSdlErrorIfNullptr(surface, "Unable to load image '" + path + "'");

        SDL_Surface* optimizedSurface = SDL_ConvertSurface(surface, SDL_GetWindowSurface(RuntimeEnvironment::getInstance().getWindow())->format, 0);
        throwSdlErrorIfNullptr(optimizedSurface, "Unable to optimize image '" + path + "'");

        return Surface(optimizedSurface);
    }

    Surface Surface::fromText(const std::string& text, const std::string& fontID, const SDL_Color fontColor, Uint32 wrapLength)
    {
        const auto font = RuntimeEnvironment::getInstance().getFont(fontID);
        const auto surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), fontColor, wrapLength);

        return Surface(surface);
    }

    SDL_Surface* Surface::expose()
    {
        return surface;
    }

    PixelCoordinates Surface::getSize() const
    {
        return size;
    }

    Uint32& Surface::pixelAt(int x, int y)
    {
        const auto& surfaceData   = reinterpret_cast<Uint8*>(surface->pixels);
        const auto& bytesPerPixel = surface->format->BytesPerPixel;
        const auto& pitch         = surface->pitch;

        Uint8* pixelAddress = static_cast<Uint8*>(surface->pixels) + (y * pitch) + x * bytesPerPixel;
        return *reinterpret_cast<Uint32*>(pixelAddress);
    }

    void Surface::fillWith(Uint32 color)
    {
        const auto& surfaceData   = reinterpret_cast<Uint8*>(surface->pixels);
        const auto& bytesPerPixel = surface->format->BytesPerPixel;
        const auto& pitch         = surface->pitch;

        Uint32* const begin = reinterpret_cast<Uint32* const>(surfaceData);
        Uint32* const end   = reinterpret_cast<Uint32* const>(surfaceData + size.y * pitch + size.x * bytesPerPixel);
        std::fill(begin, end, color);
    }

    Texture Surface::toTexture(int access) const
    {
        SDL_Texture* directTexture = SDL_CreateTextureFromSurface(rte.getRenderer(), surface);
        throwSdlErrorIfNullptr(directTexture, "Unable to create texture");

        if (access !=  SDL_TEXTUREACCESS_STATIC)
        {
            SDL_Renderer* renderer = rte.getRenderer();
            Texture modifiable(size, access);
            SDL_Texture* modifiableTexture = modifiable.expose();

            throwSdlErrorIfErrCode(SDL_SetRenderTarget(renderer, modifiableTexture), "Could not set render target to texture");
            throwSdlErrorIfErrCode(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0), "Could not set renderer draw color");
            throwSdlErrorIfErrCode(SDL_RenderFillRect(renderer, NULL), "Could not render rectangle");
            throwSdlErrorIfErrCode(SDL_RenderCopy(renderer, directTexture, nullptr, nullptr), "Could not copy texture");
            rte.resetRenderer();

            return modifiable;
        }
        else
        {
            return Texture(directTexture);
        }
    }
}
