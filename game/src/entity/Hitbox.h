
#ifndef HITBOX_H
#define HITBOX_H

#include "raylib.h"
#include <cstdint>
#include "HealthComponent.h"

struct Size
{
    float width;
    float height;
};

enum HitboxType
{
    HITBOX,
    HURTBOX,
    COLLISIONBOX,
};
// TODO: have it so that i can anchor it to top, middle, bottom;
class Hitbox
{
public:
    Color m_boxColor;
    uint32_t m_parentId;

    Rectangle getRect() { return m_rect; }
    void setCentered(bool center) { m_centered = center; }

    Hitbox(Rectangle initialPosition, Size parentSize, uint32_t parentId, Color color = RED)
    {
        m_rect = initialPosition;
        m_boxColor = color;
        m_parentSize = parentSize;
        m_parentId = parentId;
    };

    virtual bool didCollideWith(Rectangle hitbox)
    {
        return CheckCollisionRecs(m_rect, hitbox);
    };

    // TODO callable

    void onCollision(HealthComponent *health, int damage)
    {
        // Hurtboxes react no hitboxes
        if (m_type == HitboxType::HURTBOX)
        {
            health->takeDamage(damage);
        }
    }

    void setRect(float width, float height)
    {
        m_rect.width = width;
        m_rect.height = height;
    }

    void draw(bool shouldDraw)
    {
        if (shouldDraw)
            drawLines();
    }
    void move(Vector2 pos)
    {
        m_rect.x = pos.x;
        m_rect.y = pos.y;
        if (m_centered)
        {
            m_rect.x += (m_parentSize.width / 2) - (m_rect.width / 2);
            m_rect.y += (m_parentSize.height / 2) - (m_rect.height / 2);
        }
    }

    HitboxType m_type = HitboxType::COLLISIONBOX;

private:
    void drawLines()
    {
        Color outlineColor = m_boxColor;
        outlineColor.a = 255;
        DrawRectangleLines(m_rect.x, m_rect.y, m_rect.width, m_rect.height, outlineColor);
        DrawRectangle(m_rect.x, m_rect.y, m_rect.width, m_rect.height, m_boxColor);
    };
    Rectangle m_rect;
    Size m_parentSize;
    bool m_centered = true;
};
#endif