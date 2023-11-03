#ifndef BASEGRID_TXX
#define BASEGRID_TXX

#include "basegrid.h"
#include "coordinates.h"
#include "errors.h"

namespace Physics
{

    template<EitherOr<Scalar, Vector> T>
    PixelCoordinates BaseGrid<T>::getPixelSize() const
    {
        return size;
    }

    template<EitherOr<Scalar, Vector> T>
    RealCoordinates BaseGrid<T>::getRealSize() const
    {
        return toRealCoordinates(size, gridConstant);
    }

    template<EitherOr<Scalar, Vector> T>
    Real BaseGrid<T>::getGridConstant() const
    {
        return gridConstant;
    }

    template<EitherOr<Scalar, Vector> T>
    BaseGrid<T>::BaseGrid(PixelCoordinates size, Real gridConstant) :
        size(size), gridConstant(gridConstant)
    {
        if (size.x <= 0 || size.y <= 0)
        {
            throw DimensionError("Negative Grid Size");
        }
        values = std::vector<T>(size.x * size.y);
        origin = {0, 0};
    }

    template<EitherOr<Scalar, Vector> T>
    PixelCoordinates BaseGrid<T>::getPixelOrigin() const
    {
        return origin;
    }

    template<EitherOr<Scalar, Vector> T>
    RealCoordinates BaseGrid<T>::getRealOrigin() const
    {
        return toRealCoordinates(origin, gridConstant);
    }

    template<EitherOr<Scalar, Vector> T>
    void BaseGrid<T>::setOrigin(const PixelCoordinates& o)
    {
        origin = o;
    }

    template<EitherOr<Scalar, Vector> T>
    void BaseGrid<T>::setOrigin(const RealCoordinates& o)
    {
        origin = toPixelCoordinates(o, gridConstant);
    }

    template<EitherOr<Scalar, Vector> T>
    PixelCoordinates BaseGrid<T>::getMinPixelCoordinates() const
    {
        return -origin;
    }

    template<EitherOr<Scalar, Vector> T>
    PixelCoordinates BaseGrid<T>::getMaxPixelCoordinates() const
    {
        return size - origin;
    }

    template<EitherOr<Scalar, Vector> T>
    RealCoordinates BaseGrid<T>::getMinRealCoordinates() const
    {
        return toRealCoordinates(getMinPixelCoordinates(), gridConstant);
    }

    template<EitherOr<Scalar, Vector> T>
    RealCoordinates BaseGrid<T>::getMaxRealCoordinates() const
    {
        return toRealCoordinates(getMaxPixelCoordinates(), gridConstant);
    }

    template<EitherOr<Scalar, Vector> T>
    T& BaseGrid<T>::at(const RealCoordinates& c)
    {
        PixelCoordinates cp = toPixelCoordinates(c, gridConstant);
        return at(cp);
    }

    template<EitherOr<Scalar, Vector> T>
    T& BaseGrid<T>::at(const PixelCoordinates& c)
    {
        if (isWithin(c, getMinPixelCoordinates(), getMaxPixelCoordinates()))
        {
            return (*this)[c];
        }
        else
        {
            throw CoordinatesError("Coordinate out of bounds");
        }
    }

    template<EitherOr<Scalar, Vector> T>
    T& BaseGrid<T>::operator [](const PixelCoordinates& c)
    {
        const auto shifted = c + origin;
        const Pixel index = shifted.y * size.x + shifted.x;
        return values[index];
    }

    template<EitherOr<Scalar, Vector> T>
    T& BaseGrid<T>::operator [](const RealCoordinates& c)
    {
        PixelCoordinates cp = toPixelCoordinates(c, gridConstant);
        return (*this)[cp];
    }
}

#endif
