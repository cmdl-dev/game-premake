#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "entity/Entity.h"

class EntityManager
{
public:
    EntityManager(const EntityManager &) = delete;
    EntityManager &operator=(const EntityManager &) = delete;

    static EntityManager &GetInstance()
    {
        return EntityManager::s_Instance;
    }

    static void RemoveEntity(std::string key, Entity *box) { return GetInstance().impl_RemoveEntity(key, box); }
    static void AddEntities(std::string key, Entity *box) { return GetInstance().impl_AddEntity(key, box); }
    static std::vector<Entity *> GetEntitiesFor(std::vector<std::string> keys) { return GetInstance().impl_GetEntityFor(keys); }
    static std::vector<Entity *> GetAllEntities() { return GetInstance().impl_GetAllEntities(); }

private:
    static EntityManager s_Instance;
    EntityManager(){};
    bool Has(std::string);

    void impl_AddEntity(std::string key, Entity *box);
    std::vector<Entity *> impl_GetEntityFor(std::vector<std::string> keys);
    void impl_RemoveEntity(std::string key, Entity *box);
    std::vector<Entity *> impl_GetAllEntities();

    std::map<std::string, std::vector<Entity *>> m_entities;
};
#endif