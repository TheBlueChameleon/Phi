#include <algorithm>

#define UIBASE_PRIVATE
#include "ui-base/uibase.h"

using namespace Base;
namespace UiBase
{
    BaseWidget::BaseWidget(const PixelCoordinates& position, const PixelCoordinates& size) :
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

    bool BaseWidget::isActive() const
    {
        return active;
    }

    void BaseWidget::makeActive()
    {
        active = true;
    }

    void BaseWidget::makeInactive()
    {
        active = false;
    }

    PixelCoordinates BaseWidget::getPosition() const
    {
        return position;
    }

    void BaseWidget::setPosition(const PixelCoordinates& pos)
    {
        position = pos;
    }

    PixelCoordinates BaseWidget::getSize() const
    {
        return size;
    }

    void BaseWidget::setSize(const PixelCoordinates& newSize)
    {
        size = newSize;
    }
}
