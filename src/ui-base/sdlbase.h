#ifndef WINDOW_H
#define WINDOW_H

#include "ui-base/widgets/widget.h"

namespace UiBase
{
    void initUI(bool autoCallQuitUI = true);
    void quitUI();

    void loadFont(const std::string& path, int size, const std::string& ID);

    void uiMainloop();
    bool dispatch_events();
    void render_widgets();

    Widget* findWidgetAt(Base::PixelCoordinates pos);
}

#endif // WINDOW_H
