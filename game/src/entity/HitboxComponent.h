
#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "raylib.h"
#include "Hitbox.h"

class HitboxComponent : public Hitbox
{
public:
    HitboxComponent(Rectangle initialPosition, Size parentSize, uint32_t parentId, Color color = (Color){0, 121, 241, 150}) : Hitbox{initialPosition, parentSize, parentId, color}
    {
        m_type = HitboxType::HITBOX;
    };
};

#endif