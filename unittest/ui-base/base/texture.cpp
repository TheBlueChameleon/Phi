#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "ui-base/base/texture.h"
using namespace Base;
using namespace UiBase;

TEST(Texture_Suite, defaultCTor)
{
    Texture original;

    EXPECT_EQ(original.expose(), nullptr);
    EXPECT_EQ(original.getSize(), Base::PixelCoordinates({0, 0}));
}

TEST(Texture_Suite, sizeAccessCTor)
{
    std::vector<PixelCoordinates> invalidSizes(
    {
        PixelCoordinates{0, 0},
        PixelCoordinates{1, 0},
        PixelCoordinates{0, 1}

    });

    for (const auto& invalidSize : invalidSizes)
    {
        EXPECT_THROW(Texture texture(invalidSize), DimensionError);
    }

    PixelCoordinates validSize = {1, 1};
    Texture texture(validSize);

    EXPECT_NE(texture.expose(), nullptr);
    EXPECT_EQ(texture.getSize(), validSize);
}

TEST(Texture_Suite, copyCTor)
{
    PixelCoordinates validSize = {1, 1};
    Texture original(validSize);
    Texture copy(original);

    EXPECT_NE(copy.expose(), nullptr);
    EXPECT_NE(copy.expose(), original.expose());
    EXPECT_EQ(copy.getSize(), original.getSize());
}

TEST(Texture_Suite, copyAssign)
{
    PixelCoordinates validSize = {1, 1};
    Texture original(validSize);
    Texture copy;

    copy = original;

    EXPECT_NE(copy.expose(), nullptr);
    EXPECT_NE(copy.expose(), original.expose());
    EXPECT_EQ(copy.getSize(), original.getSize());
}

TEST(Texture_Suite, moveCTor)
{
    PixelCoordinates validSize = {1, 1};
    PixelCoordinates nullSize = {0, 0};

    Texture original(validSize);
    SDL_Texture* originalPtr = original.expose();
    Texture replaceMent(std::move(original));

    EXPECT_EQ(replaceMent.expose(), originalPtr);
    EXPECT_EQ(original.expose(), nullptr);

    EXPECT_EQ(replaceMent.getSize(), validSize);
    EXPECT_EQ(original.getSize(), nullSize);
}

TEST(Texture_Suite, moveAssign)
{
    PixelCoordinates validSize = {1, 1};
    PixelCoordinates nullSize = {0, 0};

    Texture original(validSize);
    SDL_Texture* originalPtr = original.expose();
    Texture replacement;

    replacement = std::move(original);

    EXPECT_EQ(replacement.expose(), originalPtr);
    EXPECT_EQ(original.expose(), nullptr);

    EXPECT_EQ(replacement.getSize(), validSize);
    EXPECT_EQ(original.getSize(), nullSize);
}
