
#ifndef HURTBOXCOMPONENT_H
#define HURTBOXCOMPONENT_H

#include "raylib.h"
#include "Hitbox.h"

class HurtboxComponent : public Hitbox
{
public:
    HurtboxComponent(Rectangle initialPosition, Size parentSize, uint32_t parentId, Color color = (Color){0, 228, 48, 150}) : Hitbox{initialPosition, parentSize, parentId, color}
    {
        m_type = HitboxType::HURTBOX;
    };
};

#endif