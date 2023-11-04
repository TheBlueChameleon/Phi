#include <iostream>

#include "physics/physics.h"
#include "ui-base/base.h"

int main()
{
    using namespace Physics;

    const auto gf = GridFactory({50, 10}, 1);
    auto world = gf.makeWorld();
    auto pot = gf.makeOverlayFromCharge(1, .05);
    auto con = gf.makeOverlayAtConstantLevel(-0.5, {5, 5});

    std::cout << "world: " << world.getPixelSize().to_string() << std::endl;
    std::cout << "pot  : " << pot.getPixelSize().to_string() << std::endl;
    std::cout << "con  : " << con.getPixelSize().to_string() << std::endl;
    //world.imposeAt(pot, PixelCoordinates {0, 0});
    world.imposeAt(con, PixelCoordinates {1, 1});

    //    std::cout << pot.to_string() << std::endl;
    std::cout << world.to_string() << std::endl;

    UiBase::foo();

    return 0;
}
