#include <SDL2/SDL.h>

#include "base/errors.h"
#include "sdlutil.h"

namespace SdlUtil
{
    std::string getSdlErrorText(const std::string& context)
    {
        return context + "\nSDL error message:\n" + SDL_GetError();
    }

    void throwSdlErrorIfNullptr(void* condition, const std::string& context)
    {
        if (condition == nullptr)
        {
            throw UiBase::SdlError(getSdlErrorText(context));
        }
    }

    void throwSdlErrorIfErrCode(int errorCode, const std::string& context)
    {
        if (errorCode != 0)
        {
            throw UiBase::SdlError(getSdlErrorText(context));
        }
    }

}
