#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
using namespace testing;

#include "physics/gridfactory.h"
using namespace Base;
using namespace Physics;

class PotentialFixture : public testing::Test
{
    protected:
        const GridFactory gf = GridFactory({20, 20}, 1.0);
        const PotentialGrid world = gf.makeWorld();
        const PotentialGrid overlay = gf.makeOverlayFromCharge(1);
};

TEST_F(PotentialFixture, fixtureStateIsSane)
{
    EXPECT_EQ(world  .getPixelSize(), (PixelCoordinates  {20, 20}));
    EXPECT_EQ(world  .getPixelOrigin(), (PixelCoordinates{ 0,  0}));
    EXPECT_EQ(overlay.getPixelSize(), (PixelCoordinates  {11, 11}));
    EXPECT_EQ(overlay.getPixelOrigin(), (PixelCoordinates{ 5,  5}));
}

TEST_F(PotentialFixture, imposePotentialsBoundariesSmall)
{
    const PixelCoordinates upperLeft = world.getMinimumImposeIndices(overlay,  {0, 0});
    const PixelCoordinates lowerRight = world.getMaximumImposeIndices(overlay, {0, 0});

    EXPECT_EQ(upperLeft, (PixelCoordinates { 5,  5}));
    EXPECT_EQ(lowerRight, (PixelCoordinates{10, 10}));
}

TEST_F(PotentialFixture, imposePotentialsBoundariesMid)
{
    const PixelCoordinates upperLeft = world.getMinimumImposeIndices(overlay,  {5, 5});
    const PixelCoordinates lowerRight = world.getMaximumImposeIndices(overlay, {5, 5});

    EXPECT_EQ(upperLeft, (PixelCoordinates { 0,  0}));
    EXPECT_EQ(lowerRight, (PixelCoordinates{10, 10}));
}

TEST_F(PotentialFixture, imposePotentialsBoundariesLarge)
{
    const PixelCoordinates upperLeft = world.getMinimumImposeIndices(overlay,  {19, 19});
    const PixelCoordinates lowerRight = world.getMaximumImposeIndices(overlay, {19, 19});

    EXPECT_EQ(upperLeft, (PixelCoordinates { 0,  0}));
    EXPECT_EQ(lowerRight, (PixelCoordinates{ 5,  5}));
}
