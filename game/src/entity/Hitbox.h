
#ifndef HITBOX_H
#define HITBOX_H

#include "raylib.h"

class Hitbox
{
public:
    Hitbox(Rectangle initialPosition, Color color = RED)
    {
        m_rect = initialPosition;
        m_boxColor = color;
    };

    Color m_boxColor;

    void draw(bool shouldDraw)
    {
        if (shouldDraw)
            drawLines();
    }
    virtual bool didCollideWith(Rectangle hitbox)
    {
        return CheckCollisionRecs(m_rect, hitbox);
    };
    void move(Vector2 pos)
    {
        m_rect.x = pos.x;
        m_rect.y = pos.y;
    }
    Rectangle getRect() { return m_rect; }

private:
    void drawLines()
    {
        DrawRectangleLines(m_rect.x, m_rect.y, m_rect.height, m_rect.width, m_boxColor);
    };
    Rectangle m_rect;
};
#endif