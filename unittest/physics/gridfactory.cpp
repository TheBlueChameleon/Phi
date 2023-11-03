#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "gridfactory.h"

TEST(GridFactory_Suite, makePotentials)
{
    using namespace Physics;

    const auto templateSize = PixelCoordinates {50, 10};
    const auto origin = PixelCoordinates{0, 0};
    const auto gridConstant = 1.0;

    const auto gf = GridFactory(templateSize, gridConstant);

    const auto world = gf.makeWorld();
    const auto createdWorldSize = world.getPixelSize();
    EXPECT_EQ(createdWorldSize, templateSize);
    EXPECT_EQ(origin, world.getPixelOrigin());

    const auto charge = 2;
    const auto cutoff = .05;
    const auto potOverlay = gf.makeOverlayFromCharge(charge, cutoff);
    const auto createdOverlaySize = potOverlay.getPixelSize();
    const auto expectedOverlaySize = PixelCoordinates{41, 21};
    EXPECT_EQ(createdOverlaySize, expectedOverlaySize);
}
