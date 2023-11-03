#include "coordinates.txx"

namespace Physics
{
    template struct Coordinates<Pixel>;
    template struct Coordinates<Real>;

    template PixelCoordinates min(const PixelCoordinates& a, const PixelCoordinates& b);
    template PixelCoordinates max(const PixelCoordinates& a, const PixelCoordinates& b);

    template RealCoordinates min(const RealCoordinates& a, const RealCoordinates& b);
    template RealCoordinates max(const RealCoordinates& a, const RealCoordinates& b);

    template std::array<Pixel, 4> getRectSorted(const PixelCoordinates& boundary1, const PixelCoordinates& boundary2);
    template std::array<Real,  4> getRectSorted(const  RealCoordinates& boundary1, const  RealCoordinates& boundary2);

    template bool isWithin<Pixel>(const PixelCoordinates& point, const PixelCoordinates& boundary1, const PixelCoordinates& boundary2);
    template bool isWithin<Real>(const Coordinates<Real>& point, const Coordinates<Real>& boundary1, const Coordinates<Real>& boundary2);

    PixelCoordinates toPixelCoordinates(const RealCoordinates& c, Real gridConstant)
    {
        return PixelCoordinates {Pixel(c.x / gridConstant), Pixel(c.y / gridConstant)};
    }

    RealCoordinates toRealCoordinates(const PixelCoordinates& c, Real gridConstant)
    {
        return RealCoordinates {c.x * gridConstant, c.y * gridConstant};
    }
}
