#include <gtest/gtest.h>

#include "ui-base/base/runtimeenvironment.h"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    // Singleton -- this affects all tests and avoids flickering
    UiBase::RuntimeEnvironment::getInstance().hideWindow();

    return RUN_ALL_TESTS();
}
