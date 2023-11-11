#ifndef RUNTIMEENVIRONMENTUSER_H
#define RUNTIMEENVIRONMENTUSER_H

#include "ui-base/base/runtimeenvironment.h"

namespace UiBase
{
    class RuntimeEnvironmentUser
    {
        protected:
            RuntimeEnvironment& rte;

        public:
            RuntimeEnvironmentUser();

            RuntimeEnvironmentUser& operator=(const RuntimeEnvironmentUser& other);
            RuntimeEnvironmentUser& operator=(RuntimeEnvironmentUser&& other);
    };
}

#endif // RUNTIMEENVIRONMENTUSER_H
