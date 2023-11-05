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
    Widget* findWidgetAt(Coords::PixelCoordinates pos);

    void render_widgets();
}

#endif // WINDOW_H
