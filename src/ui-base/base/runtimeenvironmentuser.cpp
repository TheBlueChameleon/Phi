#include <iostream>

#include "runtimeenvironmentuser.h"

namespace UiBase
{
    RuntimeEnvironmentUser::RuntimeEnvironmentUser() :
        rte(RuntimeEnvironment::getInstance())
    {}

    RuntimeEnvironmentUser& RuntimeEnvironmentUser::operator=(const RuntimeEnvironmentUser& other)
    {
        return *this;
    }

    RuntimeEnvironmentUser& RuntimeEnvironmentUser::operator=(RuntimeEnvironmentUser&& other)
    {
        return *this;
    }
}
