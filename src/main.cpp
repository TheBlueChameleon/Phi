#include <iostream>

#include "base/base.h"
#include "coords/coords.h"
#include "physics/physics.h"
#include "ui-base/uibase.h"

void show_physics()
{
    using namespace Coords;
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
}

void show_uibase()
{
    using namespace UiBase;

    initUI();
    BaseTextureButton b = BaseTextureButton::fromFile(Coords::PixelCoordinates{150,50}, "res/btn_blue.png");
    b.setTextureClicked("res/btn_red.png");
    b.setTextureMouseOver("res/btn_green.png");

    uiMainloop();
}

int main()
{
    //    show_physics();
    show_uibase();

    return 0;
}
