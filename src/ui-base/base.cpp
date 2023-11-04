#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "base.h"

namespace UiBase
{
    __attribute__((constructor))
    static void init()
    {
        std::cout << "init "<< std::endl;
    }

    __attribute__((destructor))
    static void quit()
    {
        std::cout << "quit"<< std::endl;
    }

    void foo()
    {
        std::cout << "foo"<< std::endl;
    }

}
