
#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "raylib.h"
#include "Hitbox.h"

class CollisionComponent : public Hitbox
{
public:
    CollisionComponent(Rectangle initialPosition, Size parentSize, uint32_t parentId, Color color = (Color){230, 41, 55, 150}) : Hitbox{initialPosition, parentSize, parentId, color} {};
};
#endif