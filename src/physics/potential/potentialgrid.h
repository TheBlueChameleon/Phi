#ifndef POTENTIALGRID_H
#define POTENTIALGRID_H

#include <base/basegrid.h>


namespace Physics
{
    class PotentialGrid : public BaseGrid<Scalar>
    {
        public:
            PotentialGrid(PixelCoordinates size, Real gridConstant);

            void imposeAt(const PotentialGrid potential, const PixelCoordinates at);
            void imposeAt(const PotentialGrid potential, const RealCoordinates at);

            PixelCoordinates getMinimumImposeIndices(const PotentialGrid potential, const PixelCoordinates at) const;
            PixelCoordinates getMaximumImposeIndices(const PotentialGrid potential, const PixelCoordinates at) const;

            std::string to_string() const;
    };
}

#endif // POTENTIALGRID_H
