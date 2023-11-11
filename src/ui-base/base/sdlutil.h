#ifndef SDLUTIL_H
#define SDLUTIL_H

#include <string>

namespace SdlUtil
{
    std::string getSdlErrorText(const std::string& context);
    void throwSdlErrorIfNullptr(void* condition, const std::string& context);
    void throwSdlErrorIfErrCode(int errorCode, const std::string& context);

    // TODO: img error analoga
}

#endif // SDLUTIL_H
