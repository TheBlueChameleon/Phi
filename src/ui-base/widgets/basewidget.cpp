#include <algorithm>

#define UIBASE_PRIVATE
#include "ui-base/uibase.h"

namespace UiBase
{
    BaseWidget::BaseWidget(const Coords::PixelCoordinates& position, const Coords::PixelCoordinates& size) :
        position(position), size(size)
    {
        widgets.push_back(this);
    }

    BaseWidget::~BaseWidget()
    {
        auto it = std::find(widgets.begin(), widgets.end(), this);
        widgets.erase(it);
    }

    bool BaseWidget::isVisible() const
    {
        return visible;
    }

    void BaseWidget::makeVisible()
    {
        visible = true;
    }

    void BaseWidget::makeInvisible()
    {
        visible = false;
    }

    Coords::PixelCoordinates BaseWidget::getPosition() const
    {
        return position;
    }

    void BaseWidget::setPosition(const Coords::PixelCoordinates& pos)
    {
        position = pos;
    }

    Coords::PixelCoordinates BaseWidget::getSize() const
    {
        return size;
    }

    void BaseWidget::setSize(const Coords::PixelCoordinates& newSize)
    {
        size = newSize;
    }
}
