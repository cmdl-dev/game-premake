
#ifndef UTIL_H
#define UTIL_H

#include "raylib.h"
#include "CollisionBoxManager.h"
// #include "Hitbox.h"

#include <vector>
#include <string>

namespace Util
{

    Vector2 GetAdjustedVectorFromCollision(Hitbox *collisionBox, std::vector<std::string> groups, Vector2 calculatedVector);
}

#endif