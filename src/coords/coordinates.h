#ifndef COORDINATES_H
#define COORDINATES_H

#include <array>
#include <concepts>
#include <string>

#include "base/base.h"

namespace Coords
{
    using Pixel = int;
    using Real = double;

    template<typename T>
    concept PixelOrReal = Base::EitherOr<T, Pixel, Real>;

    template<PixelOrReal T>
    struct Coordinates
    {
        T x;
        T y;

        Coordinates<T> operator-() const;
        Coordinates<T> operator+(const Coordinates<T>& rhs) const;
        Coordinates<T> operator-(const Coordinates<T>& rhs) const;
        Coordinates<T> operator*(const Real rhs) const;
        Coordinates<T> operator/(const Real rhs) const;
        bool operator==(const Coordinates<T>& rhs) const;

        std::string to_string() const;
    };

    using PixelCoordinates = Coordinates<Pixel>;
    using RealCoordinates = Coordinates<Real>;

    using Scalar = Real;
    using Vector = RealCoordinates;

    template<PixelOrReal T>
    Coordinates<T> min(const Coordinates<T>& a, const Coordinates<T>& b);

    template<PixelOrReal T>
    Coordinates<T> max(const Coordinates<T>& a, const Coordinates<T>& b);

    template<PixelOrReal T>
    std::array<T, 4> getRectSorted(const Coordinates<T>& boundary1, const Coordinates<T>& boundary2);

    template<PixelOrReal T>
    bool isWithin(const Coordinates<T>& point, const Coordinates<T>& boundary1, const Coordinates<T>& boundary2);

    PixelCoordinates toPixelCoordinates(const RealCoordinates& c, Real gridConstant);
    RealCoordinates  toRealCoordinates(const PixelCoordinates& c, Real gridConstant);
}

#endif // COORDINATES_H
