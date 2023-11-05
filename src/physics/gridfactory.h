#ifndef GRIDFACTORY_H
#define GRIDFACTORY_H

#include "coords/coordinates.h"
#include "potential/potentialgrid.h"

namespace Physics
{
    class GridFactory
    {
        private:
            static const Coords::PixelCoordinates USE_DEFAULT;

            Coords::PixelCoordinates size;
            Coords::Real gridConstant;

        public:
            GridFactory(Coords::PixelCoordinates size, Coords::Real gridConstant);

            PotentialGrid makeWorld() const;
            PotentialGrid makeOverlayAtConstantLevel(Coords::Real level, Coords::PixelCoordinates size = USE_DEFAULT) const;
            PotentialGrid makeOverlayFromCharge(Coords::Real charge, Coords::Real cutoff = 0.1) const;
    };
}

#endif // GRIDFACTORY_H
