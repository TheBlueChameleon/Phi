#ifndef POTENTIALGRID_H
#define POTENTIALGRID_H

#include <base/basegrid.h>


namespace Physics
{
    class PotentialGrid : public BaseGrid<Scalar>
    {
        private:
            void imposeImpl_noAcceleration(const PotentialGrid& potential, const PixelCoordinates& minIdxs, const PixelCoordinates& maxIdxs, const PixelCoordinates& startIdxs);
            void imposeImpl_avxAccelerated();

        public:
            PotentialGrid();
            PotentialGrid(PixelCoordinates size, Real gridConstant, Real level = 0);

            PixelCoordinates getMinimumImposeIndices(const PotentialGrid& potential, const PixelCoordinates at) const;
            PixelCoordinates getMaximumImposeIndices(const PotentialGrid& potential, const PixelCoordinates at) const;

            void imposeAt(const PotentialGrid& potential, const RealCoordinates  at);
            void imposeAt(const PotentialGrid& potential, const PixelCoordinates at);

            std::string to_string() const;
    };
}

#endif // POTENTIALGRID_H
