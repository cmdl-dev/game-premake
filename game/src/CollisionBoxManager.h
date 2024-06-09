#ifndef COLLISIONBOXMANAGER_H
#define COLLISIONBOXMANAGER_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "CollisionBox.h"

class CollisionBoxManager
{
public:
    CollisionBoxManager(const CollisionBoxManager &) = delete;
    CollisionBoxManager &operator=(const CollisionBoxManager &) = delete;

    static CollisionBoxManager &GetInstance()
    {
        return CollisionBoxManager::s_Instance;
    }

    static void AddCollisionBox(std::string key, CollisionBox *box) { return GetInstance().impl_AddCollisionBox(key, box); }
    static std::vector<CollisionBox *> GetCollisionBoxesFor(std::vector<std::string> keys) { return GetInstance().impl_GetCollisionBoxesFor(keys); }

private:
    static CollisionBoxManager s_Instance;
    CollisionBoxManager(){};
    bool Has(std::string);

    void impl_AddCollisionBox(std::string key, CollisionBox *box);
    std::vector<CollisionBox *> impl_GetCollisionBoxesFor(std::vector<std::string> keys);

    std::map<std::string, std::vector<CollisionBox *>> m_CollisionBoxes;
};
#endif