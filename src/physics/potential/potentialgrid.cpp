#include <algorithm>
#include <iostream>
#include <ranges>

#include "potentialgrid.h"

namespace Physics
{
    PotentialGrid::PotentialGrid(PixelCoordinates size, Real gridConstant) : BaseGrid<Scalar>(size, gridConstant) {}

    template<EitherOr<Pixel, Real> T>
    T negativeReLU(T x)
    {
        return x >= 0 ? 0 : - x;
    }

    constexpr PixelCoordinates offByOne = {1,1};

    PixelCoordinates PotentialGrid::getMinimumImposeIndices(const PotentialGrid potential, const PixelCoordinates at) const
    {
        PixelCoordinates minPos = at - (potential.size - potential.origin + this->origin) + offByOne;
        return {negativeReLU(minPos.x), negativeReLU(minPos.y)};
    }

    PixelCoordinates PotentialGrid::getMaximumImposeIndices(const PotentialGrid potential, const PixelCoordinates at) const
    {
        PixelCoordinates maxPos = at + potential.getMaxPixelCoordinates() + this->origin - offByOne;
        PixelCoordinates clippedPos = min(maxPos, this->getMaxPixelCoordinates() - offByOne);
        PixelCoordinates deltaClipping = maxPos - clippedPos;
        PixelCoordinates existingPos = potential.size - deltaClipping - offByOne;

        return existingPos;
    }

    void PotentialGrid::imposeAt(const PotentialGrid potential, const PixelCoordinates at)
    {
        PixelCoordinates minIdxs = getMinimumImposeIndices(potential, at);
        PixelCoordinates maxIdxs = getMaximumImposeIndices(potential, at);
    }

    void PotentialGrid::imposeAt(const PotentialGrid potential, const RealCoordinates at)
    {
        const PixelCoordinates pc = toPixelCoordinates(at, gridConstant);
        imposeAt(potential, pc);
    }

    std::string PotentialGrid::to_string() const
    {
        constexpr char shades[] = "?Vv=- +*tT!";

        const int length = size.x * size.y + size.y;
        auto result = std::string(length, 'x');

        const Real min = *std::min_element(values.begin(), values.end());
        const Real max = *std::max_element(values.begin(), values.end());
        const Real width = max - min;

        int idx_string = 0, idx_field = 0;
        for (int y = 0; y < size.y; ++y)
        {
            for (int x = 0; x < size.x; ++x)
            {
                const int level = ((values[idx_field] - min) / width) * (sizeof(shades) - 2);
                result[idx_string] = shades[level];
                ++idx_field;
                ++idx_string;
            }
            result[idx_string] = '\n';
            ++idx_string;
        }

        return result;
    }
}
