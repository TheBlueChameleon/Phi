#ifndef COORDINATES_H
#define COORDINATES_H

#include <array>
#include <concepts>
#include <string>

namespace Coords
{
    template<typename T, typename E, typename O>
    concept EitherOr = std::is_convertible_v<T, E> || std::is_convertible_v<T, O>;

    using Pixel = int;
    using Real = double;

    template<EitherOr<Pixel, Real> T>
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

    template<EitherOr<Pixel, Real> T>
    Coordinates<T> min(const Coordinates<T>& a, const Coordinates<T>& b);

    template<EitherOr<Pixel, Real> T>
    Coordinates<T> max(const Coordinates<T>& a, const Coordinates<T>& b);

    template<EitherOr<Pixel, Real> T>
    std::array<T, 4> getRectSorted(const Coordinates<T>& boundary1, const Coordinates<T>& boundary2);

    template<EitherOr<Pixel, Real> T>
    bool isWithin(const Coordinates<T>& point, const Coordinates<T>& boundary1, const Coordinates<T>& boundary2);

    PixelCoordinates toPixelCoordinates(const RealCoordinates& c, Real gridConstant);
    RealCoordinates  toRealCoordinates(const PixelCoordinates& c, Real gridConstant);
}

#endif // COORDINATES_H
