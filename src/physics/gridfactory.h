#ifndef GRIDFACTORY_H
#define GRIDFACTORY_H

#include "base/coordinates.h"
#include "potential/potentialgrid.h"

namespace Physics
{
    class GridFactory
    {
        private:
            PixelCoordinates size;
            Real gridConstant;

        public:
            GridFactory(PixelCoordinates size, Real gridConstant);

            PotentialGrid makeWorld() const;
            PotentialGrid makeOverlayFromCharge(Real charge, Real cutoff = 0.1) const;
    };
}

#endif // GRIDFACTORY_H
