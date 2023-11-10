#include <string>
using namespace std::string_literals;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "base/errors.h"

#include "surface.h"
#define SDL_PRIVATE
#include "globals.h"

using namespace Base;
namespace UiBase
{
    Surface::Surface(const PixelCoordinates& size) :
        size(size)
    {
        //(Uint32 flags, int width, int height, int depth, Uint32 format);
        surface = SDL_CreateRGBSurfaceWithFormat(
                      0,
                      size.x, size.y, 32,
                      SDL_GetWindowSurface(window)->format->format
                  );
    }

    Surface::Surface(SDL_Surface* surface) :
        surface(surface),
        size({surface->w, surface->h})
    {}

    Surface::~Surface()
    {
        if (surface)
        {
            SDL_FreeSurface(surface);
        }
    }

    Surface Surface::fromFile(const std::string& path)
    {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == NULL)
        {
            throw SdlError("Unable to load image '"s + path + "'\n"
                           "SDL_image Error: "s +IMG_GetError());
        }

        SDL_Surface* optimizedSurface = SDL_ConvertSurface(surface, SDL_GetWindowSurface(window)->format, 0);
        if (optimizedSurface == NULL)
        {
            throw SdlError("Unable to optimize image '"s + path.c_str() + "'\nSDL Error: \n"s + SDL_GetError());
        }

        return Surface(optimizedSurface);
    }

    Texture Surface::toTexture() const
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL)
        {
            throw SdlError("Unable to create texture \n"
                           "SDL_image Error: "s +IMG_GetError());
        }

        return Texture(texture);
    }
}
