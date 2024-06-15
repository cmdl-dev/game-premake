#ifndef DEBUGMENU_H
#define DEBUGMENU_H
#include "entity/Entity.h"
#include "DebugWindow.h"

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
    Entity *m_selectedEntity;
    AnimationWindow *m_animWindow;
};
#endif
