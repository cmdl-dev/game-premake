#ifndef DEBUGMENU_H
#define DEBUGMENU_H

class DebugMenu
{

public:
    DebugMenu();
    ~DebugMenu();
    void handleEvents();
    void newFrame();
    void update();
    void draw();
};
#endif