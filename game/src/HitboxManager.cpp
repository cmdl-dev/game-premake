
#include <iostream>

#include "HitboxManager.h"

HitboxManager HitboxManager::s_Instance;
void HitboxManager::impl_AddCollisionBox(std::string key, Hitbox *box)
{
    HitboxManager &manager = HitboxManager::GetInstance();
    bool has = manager.Has(key);
    if (!has)
    {
        manager.m_CollisionBoxes[key] = std::vector<Hitbox *>{box};
        return;
    }
    manager.m_CollisionBoxes[key].push_back(box);
}

std::vector<Hitbox *> HitboxManager::impl_GetCollisionBoxesFor(std::vector<std::string> keys)
{
    std::vector<Hitbox *> boxes;
    HitboxManager &manager = HitboxManager::GetInstance();

    for (auto key : keys)
    {
        if (manager.Has(key))
        {
            std::vector<Hitbox *> keyBoxes = manager.m_CollisionBoxes[key];
            boxes.insert(boxes.end(), keyBoxes.begin(), keyBoxes.end());
        }
    }

    return boxes;
}

bool HitboxManager::Has(std::string key)
{
    HitboxManager &manager = HitboxManager::GetInstance();
    return manager.m_CollisionBoxes.find(key) != manager.m_CollisionBoxes.end();
}
