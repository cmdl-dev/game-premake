#ifndef DEBUGMENU_H
#define DEBUGMENU_H
#include "EntityDebugMenu.h"

class DebugMenu
{
public:
    DebugMenu();
    ~DebugMenu();
    void handleEvents();
    void newFrame();
    void update();
    void draw();

private:
    EntityDebugMenu *m_EntDebugMenu;
};

#endif
