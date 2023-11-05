#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include "ui-base/widgets/widget.h"

namespace UiBase
{
    void initUI(bool autoCallQuitUI = true);
    void quitUI();

    void uiMainloop();

    bool dispatch_events();
    Widget* findWidgetAt(Coords::PixelCoordinates pos);

    void render_widgets();
}

#endif // WINDOW_H
