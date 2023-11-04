#ifndef GRIDFACTORY_H
#define GRIDFACTORY_H

#include "coords/coordinates.h"
#include "potential/potentialgrid.h"

namespace Physics
{
    class GridFactory
    {
        private:
            static const PixelCoordinates USE_DEFAULT;

            PixelCoordinates size;
            Real gridConstant;

        public:
            GridFactory(PixelCoordinates size, Real gridConstant);

            PotentialGrid makeWorld() const;
            PotentialGrid makeOverlayAtConstantLevel(Real level, PixelCoordinates size = USE_DEFAULT) const;
            PotentialGrid makeOverlayFromCharge(Real charge, Real cutoff = 0.1) const;
    };
}

#endif // GRIDFACTORY_H
