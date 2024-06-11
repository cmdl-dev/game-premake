
#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "raylib.h"
#include "Hitbox.h"

class CollisionComponent : public Hitbox
{
public:
    CollisionComponent(Rectangle initialPosition, Color color = RED) : Hitbox{initialPosition, color} {};
};
#endif