#include <iostream>

#include "base/base.h"
#include "physics/physics.h"
#include "ui-base/ui-base.h"
#include "ui-base/widgets/impl/texturelabel.h"

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

    rte.loadFont("mono16", "res/FreeMono.ttf", 16, TTF_STYLE_BOLD);

    TextureButton buttonDragDroppable = TextureButton::fromFile(PixelCoordinates{150,50}, "res/btn_blue.png");
    buttonDragDroppable.setTextureClicked(Texture::fromFile("res/btn_red.png"));
    buttonDragDroppable.setTextureMouseOver(Texture::fromFile("res/btn_green.png"));
    buttonDragDroppable.makeDragDropCapable();
    // TOOD: add this to testing b.setSize({0,0}); -- throws Base::AccessRightsError

    TextureButton buttonClickable = TextureButton::fromFile(PixelCoordinates{350,50}, "res/btn_blue.png");
    buttonClickable.setEventHandler(Callbacks::Clicked, [](const SDL_Event& e)
    {
        std::cout << "callback triggered" << std::endl;
    });

    Surface flowSurface({256, 50}, 0);
    for (auto y = 0; y < 50; ++y)
    {
        for (auto x = 0; x < 256; ++x)
        {
            flowSurface.pixelAt(x, y) = (x << 16) + ((x & 0xFE) << 7) + ((x & 0xFC) >> 1);
        }
    }
    Texture flow = flowSurface.toTexture();
    TextureButton b0(PixelCoordinates{150,120}, flowSurface.toTexture());

    TextureLabel lbl = TextureLabel({150, 200}, {0, 0}, "mono16");
    lbl.suspendUpdateRendering();
    lbl.setText("foo thy bars");
    lbl.setColor(SdlColors::green);
    lbl.setBackdrop(flow);
    lbl.resumeUpdateRendering();

    rte.mainloop();
}

int main()
{
    //    show_physics();
    show_uibase();

    return 0;
}
