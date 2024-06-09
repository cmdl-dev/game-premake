
#include <iostream>

#include "CollisionBoxManager.h"

CollisionBoxManager CollisionBoxManager::s_Instance;
void CollisionBoxManager::impl_AddCollisionBox(std::string key, CollisionBox *box)
{
    CollisionBoxManager &manager = CollisionBoxManager::GetInstance();
    bool has = manager.Has(key);
    if (!has)
    {
        manager.m_CollisionBoxes[key] = std::vector<CollisionBox *>{box};
        return;
    }
    manager.m_CollisionBoxes[key].push_back(box);
}

std::vector<CollisionBox *> CollisionBoxManager::impl_GetCollisionBoxesFor(std::vector<std::string> keys)
{
    std::vector<CollisionBox *> boxes;
    CollisionBoxManager &manager = CollisionBoxManager::GetInstance();

    for (auto key : keys)
    {
        if (manager.Has(key))
        {
            std::vector<CollisionBox *> keyBoxes = manager.m_CollisionBoxes[key];
            boxes.insert(boxes.end(), keyBoxes.begin(), keyBoxes.end());
        }
    }

    return boxes;
}

bool CollisionBoxManager::Has(std::string key)
{
    CollisionBoxManager &manager = CollisionBoxManager::GetInstance();
    return manager.m_CollisionBoxes.find(key) != manager.m_CollisionBoxes.end();
}
