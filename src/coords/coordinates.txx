#ifndef COORDINATES_TXX
#define COORDINATES_TXX

#include "coordinates.h"

namespace Coords
{
    // ====================================================================== //
    // class methods

    // todo: optimize in terms of intrinsics
    template<EitherOr<Pixel, Real> T>
    Coordinates<T> Coordinates<T>::operator-() const
    {
        return {-this->x, -this->y};
    }

    template<EitherOr<Pixel, Real> T>
    Coordinates<T> Coordinates<T>::operator+(const Coordinates<T>& rhs) const
    {
        return {this->x + rhs.x, this->y + rhs.y};
    }

    template<EitherOr<Pixel, Real> T>
    Coordinates<T> Coordinates<T>::operator-(const Coordinates<T>& rhs) const
    {
        return {this->x - rhs.x, this->y - rhs.y};
    }

    template<EitherOr<Pixel, Real> T>
    Coordinates<T> Coordinates<T>::operator*(const Real rhs) const
    {
        return {static_cast<T>(this->x * rhs), static_cast<T>(this->y * rhs)};
    }

    template<EitherOr<Pixel, Real> T>
    Coordinates<T> Coordinates<T>::operator/(const Real rhs) const
    {
        return {static_cast<T>(this->x / rhs), static_cast<T>(this->y / rhs)};
    }

    template<EitherOr<Pixel, Real> T>
    bool Coordinates<T>::operator==(const Coordinates<T>& rhs) const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }

    template<EitherOr<Pixel, Real> T>
    std::string Coordinates<T>::to_string() const
    {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }

    // ====================================================================== //
    // helper functions

    template<EitherOr<Pixel, Real> T>
    Coordinates<T> min(const Coordinates<T>& a, const Coordinates<T>& b)
    {
        return { std::min(a.x, b.x), std::min(a.y, b.y) };
    }

    template<EitherOr<Pixel, Real> T>
    Coordinates<T> max(const Coordinates<T>& a, const Coordinates<T>& b)
    {
        return { std::max(a.x, b.x), std::max(a.y, b.y) };
    }

    template<EitherOr<Pixel, Real> T>
    std::array<T, 4> getRectSorted(const Coordinates<T>& boundary1, const Coordinates<T>& boundary2)
    {
        T x1 = boundary1.x;
        T x2 = boundary2.x;
        T y1 = boundary1.y;
        T y2 = boundary2.y;

        // *INDENT-OFF*
        if (x1 > x2) {std::swap(x1, x2);}
        if (y1 > y2) {std::swap(y1, y2);}
        // *INDENT-ON*

        return {x1, x2, y1, y2};
    }

    template<EitherOr<Pixel, Real> T>
    bool isWithin(const Coordinates<T>& point, const Coordinates<T>& boundary1, const Coordinates<T>& boundary2)
    {
        const auto [x1, x2, y1, y2] = getRectSorted(boundary1, boundary2);

        if (x1 <= point.x && point.x < x2)
        {
            if (y1 <= point.y && point.y < y2)
            {
                return true;
            }
        }
        return false;
    }
}

#endif // COORDINATES_TXX
