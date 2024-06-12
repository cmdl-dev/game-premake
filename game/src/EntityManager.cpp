#include <iostream>
#include "EntityManager.h"

EntityManager EntityManager::s_Instance;
void EntityManager::impl_AddEntity(std::string key, Entity *box)
{
    EntityManager &manager = EntityManager::GetInstance();
    bool has = manager.Has(key);
    if (!has)
    {
        manager.m_entities[key] = std::vector<Entity *>{box};
        return;
    }
    manager.m_entities[key].push_back(box);
}

std::vector<Entity *> EntityManager::impl_GetEntityFor(std::vector<std::string> keys)
{
    std::vector<Entity *> boxes;
    EntityManager &manager = EntityManager::GetInstance();

    for (auto key : keys)
    {
        if (manager.Has(key))
        {
            std::vector<Entity *> keyBoxes = manager.m_entities[key];
            boxes.insert(boxes.end(), keyBoxes.begin(), keyBoxes.end());
        }
    }

    return boxes;
}

bool EntityManager::Has(std::string key)
{
    EntityManager &manager = EntityManager::GetInstance();
    return manager.m_entities.find(key) != manager.m_entities.end();
}
