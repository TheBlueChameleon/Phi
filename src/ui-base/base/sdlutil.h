#ifndef SDLUTIL_H
#define SDLUTIL_H

#include <string>

#include <SDL2/SDL.h>

namespace SdlUtil
{
    std::string getSdlErrorText(const std::string& context);
    void throwSdlErrorIfNullptr(void* condition, const std::string& context);
    void throwSdlErrorIfErrCode(int errorCode, const std::string& context);
}

namespace SdlColors
{
    constexpr SDL_Color
    white       = {255, 255, 255, 255},
    grey        = {128, 128, 128, 255},
    black       = {  0,   0,   0, 255},
    red         = {255,   0,   0, 255},
    green       = {  0, 255,   0, 255},
    blue        = {  0,   0, 255, 255},
    yellow      = {255, 255,   0, 255},
    purple      = {255,   0, 255, 255},
    cyan        = {  0, 255, 255, 255},
    dark_red    = {128,   0,   0, 255},
    dark_green  = {  0, 128,   0, 255},
    dark_blue   = {  0,   0, 128, 255},
    brown       = {128, 128,   0, 255},
    dark_purple = {128,   0, 128, 255},
    dark_cyan   = {  0, 128, 128, 255},
    transparent = {  0,   0,   0,   0};
};
#endif // SDLUTIL_H
