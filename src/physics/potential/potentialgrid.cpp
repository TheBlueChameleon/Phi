#include <algorithm>
#include <iostream>
#include <ranges>

#include "potentialgrid.h"

namespace Physics
{
    PotentialGrid::PotentialGrid() : BaseGrid<Scalar>({0,0}, 0) {}

    PotentialGrid::PotentialGrid(PixelCoordinates size, Real gridConstant, Real level) : BaseGrid<Scalar>(size, gridConstant)
    {
        std::fill(values.begin(), values.end(), level);
    }

    template<EitherOr<Pixel, Real> T>
    T negativeReLU(T x)
    {
        return x >= 0 ? 0 : - x;
    }

    constexpr PixelCoordinates offByOne = {1,1};

    PixelCoordinates PotentialGrid::getMinimumImposeIndices(const PotentialGrid& potential, const PixelCoordinates at) const
    {
        PixelCoordinates minPos = at - (potential.size - potential.origin + this->origin) + offByOne;
        return {negativeReLU(minPos.x), negativeReLU(minPos.y)};
    }

    PixelCoordinates PotentialGrid::getMaximumImposeIndices(const PotentialGrid& potential, const PixelCoordinates at) const
    {
        PixelCoordinates maxPos = at + potential.getMaxPixelCoordinates() + this->origin - offByOne;
        PixelCoordinates clippedPos = min(maxPos, this->getMaxPixelCoordinates() - offByOne);
        PixelCoordinates deltaClipping = maxPos - clippedPos;
        PixelCoordinates existingPos = potential.size - deltaClipping - offByOne;

        return existingPos;
    }

    void PotentialGrid::imposeAt(const PotentialGrid& potential, const RealCoordinates at)
    {
        const PixelCoordinates pc = toPixelCoordinates(at, gridConstant);
        imposeAt(potential, pc);
    }

    void PotentialGrid::imposeAt(const PotentialGrid& potential, const PixelCoordinates at)
    {
        PixelCoordinates minIdxs = getMinimumImposeIndices(potential, at);
        PixelCoordinates maxIdxs = getMaximumImposeIndices(potential, at);
        PixelCoordinates startIdxs = origin + at - potential.origin + minIdxs;

#ifdef NO_AVX_ACCELERATION
        imposeImpl_noAcceleration(potential, minIdxs, maxIdxs, startIdxs);
#else
        imposeImpl_avxAccelerated();
#endif
    }

    int to_index(int x, int y, int w)
    {
        return y * w + x;
    }

    void PotentialGrid::imposeImpl_noAcceleration(const PotentialGrid& potential, const PixelCoordinates& minIdxs, const PixelCoordinates& maxIdxs, const PixelCoordinates& startIdxs)
    {
        const auto width = maxIdxs.x - minIdxs.x;
        const auto potBegin  = potential.values.begin();
        const auto selfBegin = this->values.begin();

        for (auto y = minIdxs.y; y <= maxIdxs.y; ++y)
        {
            const auto from = to_index(minIdxs.x, y, potential.size.x);
            const auto till = from + width;
            const auto to   = to_index(startIdxs.x, startIdxs.y + y - minIdxs.y, size.x);

            std::transform(potBegin + from, potBegin + till,
                           selfBegin + to,
                           selfBegin + to,
                           std::plus<> {}
                          );
        }
    }

    void PotentialGrid::imposeImpl_avxAccelerated() {}



    std::string PotentialGrid::to_string() const
    {
        constexpr char shades[] = "?Vv=- +*tT!";

        const int length = size.x * size.y + size.y;
        auto result = std::string(length, 'x');

        const Real min = *std::min_element(values.begin(), values.end());
        const Real max = *std::max_element(values.begin(), values.end());
        const Real width = max - min;

        if (width == 0)
        {
            return "(flat potential)";
        }

        const Real factor = (sizeof(shades) - 2) / width;
        int idx_string = 0, idx_field = 0;
        for (int y = 0; y < size.y; ++y)
        {
            for (int x = 0; x < size.x; ++x)
            {
                const int level = (values[idx_field] - min) * factor;
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

