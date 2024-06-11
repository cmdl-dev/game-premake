#ifndef COLLISIONBOXMANAGER_H
#define COLLISIONBOXMANAGER_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "entity/Hitbox.h"

class CollisionBoxManager
{
public:
    CollisionBoxManager(const CollisionBoxManager &) = delete;
    CollisionBoxManager &operator=(const CollisionBoxManager &) = delete;

    static CollisionBoxManager &GetInstance()
    {
        return CollisionBoxManager::s_Instance;
    }

    static void AddCollisionBox(std::string key, Hitbox *box) { return GetInstance().impl_AddCollisionBox(key, box); }
    static std::vector<Hitbox *> GetCollisionBoxesFor(std::vector<std::string> keys) { return GetInstance().impl_GetCollisionBoxesFor(keys); }

private:
    static CollisionBoxManager s_Instance;
    CollisionBoxManager(){};
    bool Has(std::string);

    void impl_AddCollisionBox(std::string key, Hitbox *box);
    std::vector<Hitbox *> impl_GetCollisionBoxesFor(std::vector<std::string> keys);

    std::map<std::string, std::vector<Hitbox *>> m_CollisionBoxes;
};
#endif