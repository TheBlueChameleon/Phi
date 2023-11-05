#ifndef POTENTIALGRID_H
#define POTENTIALGRID_H

#include "coords/basegrid.h"

namespace Physics
{
    class PotentialGrid : public Coords::BaseGrid<Coords::Scalar>
    {

        private:
            void imposeImpl_noAcceleration(const PotentialGrid& potential, const Coords::PixelCoordinates& minIdxs, const Coords::PixelCoordinates& maxIdxs, const Coords::PixelCoordinates& startIdxs);
            void imposeImpl_avxAccelerated(const PotentialGrid& potential, const Coords::PixelCoordinates& minIdxs, const Coords::PixelCoordinates& maxIdxs, const Coords::PixelCoordinates& startIdxs);

        public:
            PotentialGrid();
            PotentialGrid(Coords::PixelCoordinates size, Coords::Real gridConstant, Coords::Real level = 0);

            Coords::PixelCoordinates getMinimumImposeIndices(const PotentialGrid& potential, const Coords::PixelCoordinates at) const;
            Coords::PixelCoordinates getMaximumImposeIndices(const PotentialGrid& potential, const Coords::PixelCoordinates at) const;

            void imposeAt(const PotentialGrid& potential, const Coords::RealCoordinates  at);
            void imposeAt(const PotentialGrid& potential, const Coords::PixelCoordinates at);

            std::string to_string() const;
    };
}

#endif // POTENTIALGRID_H
