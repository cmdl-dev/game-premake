#include "CollisionBoxManager.h"
#include <iostream>
// std::vector<CollisionBox> CollisionBoxManager::m_CollisionBoxes;
// std::map<std::string, std::vector<CollisionBox>> CollisionBoxes;
// void CollisionBoxManager::impl_AddCollisionBox(std::string key, CollisionBox *box)

CollisionBoxManager CollisionBoxManager::s_Instance;
void CollisionBoxManager::AddCollisionBox(std::string key, CollisionBox *box)
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

// std::vector<CollisionBox *> CollisionBoxManager::impl_GetCollisionBoxesFor(std::string key)
std::vector<CollisionBox *> CollisionBoxManager::GetCollisionBoxesFor(std::string key)
{
    CollisionBoxManager &manager = CollisionBoxManager::GetInstance();
    if (!manager.Has(key))
        return std::vector<CollisionBox *>{};
    return manager.m_CollisionBoxes[key];
}

bool CollisionBoxManager::Has(std::string key)
{
    CollisionBoxManager &manager = CollisionBoxManager::GetInstance();
    return manager.m_CollisionBoxes.find(key) != manager.m_CollisionBoxes.end();
}
