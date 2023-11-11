#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "ui-base/base/runtimeenvironment.h"
using namespace UiBase;

TEST(UiBase_Suite, invisibleForTesting)
{
    EXPECT_EQ(RuntimeEnvironment::getInstance().isWindowShown(), false);
}
