#include <iostream>

#include "physics.h"

int main()
{
    using namespace Physics;

    const auto gf = GridFactory({50, 10}, 1);
    auto world = gf.makeWorld();
    auto pot = gf.makeOverlayFromCharge(1, .05);

    std::cout << pot.to_string() << std::endl;

    return 0;
}
