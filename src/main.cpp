#include <iostream>

#include "base/base.h"
#include "physics/physics.h"
#include "ui-base/ui-base.h"

void show_physics()
{
    using namespace Base;
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
    using namespace Base;
    using namespace UiBase;

    auto& rte = RuntimeEnvironment::getInstance();
    std::cout << "RTE instantiated at " << &rte << std::endl;
    TextureButton b = TextureButton::fromFile(PixelCoordinates{150,50}, "res/btn_blue.png");
    b.setTextureClicked(Texture::fromFile("res/btn_red.png"));
    b.setTextureMouseOver(Texture::fromFile("res/btn_green.png"));
    b.makeDragDropCapable();
    TextureButton c = TextureButton::fromFile(PixelCoordinates{350,50}, "res/btn_blue.png");
    c.setEventHandler(Callbacks::Clicked, [](const SDL_Event& e)
    {
        std::cout << "callback triggered" << std::endl;
    });
    std::cout << "button instantiated" << std::endl;
    std::cout << "  " << b.getSize().to_string() << std::endl;

    std::cout << "passing to mainloop" << std::endl;

    rte.mainloop();
}

int main()
{
    //    show_physics();
    show_uibase();

    return 0;
}
