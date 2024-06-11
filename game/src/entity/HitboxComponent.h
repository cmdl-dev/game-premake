
#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "raylib.h"
#include "Hitbox.h"

class HitboxComponent : public Hitbox
{
public:
    HitboxComponent(Rectangle initialPosition, Color color = YELLOW) : Hitbox{initialPosition, color} {};
};

#endif