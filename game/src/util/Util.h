
#ifndef UTIL_H
#define UTIL_H

#include "raylib.h"
#include "HitboxManager.h"
// #include "Hitbox.h"

#include <vector>
#include <string>

namespace Util
{

    Vector2 GetAdjustedVectorFromCollision(Hitbox *collisionBox, std::vector<std::string> groups, Vector2 calculatedVector);
    // class Utility {
    // public :
    //     static int getUniqueId();
    // };

    // int Utility::getUniqueId() {
    //     static std::atomic<std::uint32_t> uid { 0 };
    //     return ++uid;
    // }
    class UniqueId
    {
    public:
        static int getUniqueId();
    };
}

#endif