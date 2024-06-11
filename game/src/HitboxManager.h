#ifndef HITBOXMANAGER_H
#define HITBOXMANAGER_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "entity/Hitbox.h"

class HitboxManager
{
public:
    HitboxManager(const HitboxManager &) = delete;
    HitboxManager &operator=(const HitboxManager &) = delete;

    static HitboxManager &GetInstance()
    {
        return HitboxManager::s_Instance;
    }

    static void AddCollisionBox(std::string key, Hitbox *box) { return GetInstance().impl_AddCollisionBox(key, box); }
    static std::vector<Hitbox *> GetCollisionBoxesFor(std::vector<std::string> keys) { return GetInstance().impl_GetCollisionBoxesFor(keys); }

private:
    static HitboxManager s_Instance;
    HitboxManager(){};
    bool Has(std::string);

    void impl_AddCollisionBox(std::string key, Hitbox *box);
    std::vector<Hitbox *> impl_GetCollisionBoxesFor(std::vector<std::string> keys);

    std::map<std::string, std::vector<Hitbox *>> m_CollisionBoxes;
};
#endif