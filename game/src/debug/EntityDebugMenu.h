
#ifndef ENTITYDEBUGMENU_H
#define ENTITYDEBUGMENU_H

#include "../entity/Entity.h"
#include "DebugWindow.h"

class EntityDebugMenu
{
public:
    EntityDebugMenu();

    void selectNewEntity(Entity *e);

    void handleEvents();
    void update();
    void show();
    /******************
     * Getters / Setters
     ******************/
    void toggleClicksEnabled() { m_clicksEnabled ? disableClicks() : enableClicks(); }
    void enableClicks() { m_clicksEnabled = true; }
    void disableClicks()
    {
        m_clicksEnabled = false;
        removedSelectedEntity();
        unLockEntity();
    }
    Entity *getEntity() { return m_selectedEntity; }

private:
    bool m_lockSelectedEntity = false;
    bool m_clicksEnabled = true;
    Entity *m_selectedEntity = nullptr;
    AnimationWindow m_animationWindow;

    void showDebugBanner();
    void removedSelectedEntity()
    {
        if (m_selectedEntity != nullptr)
            m_selectedEntity = nullptr;
    }
    void lockEntity() { m_lockSelectedEntity = true; };
    void unLockEntity() { m_lockSelectedEntity = false; };
    void toggleLockEntity() { m_lockSelectedEntity ? unLockEntity() : lockEntity(); }

    void showGeneralSection();
    void showHitboxSection();
    void showAnimationSection();
};

#endif