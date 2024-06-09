#ifndef COLISIONBOX_H
#define COLISIONBOX_H

#include "raylib.h"
class CollisionBox
{
public:
    CollisionBox(Rectangle rect);
    void draw();
    void update(Vector2 newPosition);

    bool isCollidingWith(Rectangle box);
    int getHeight()
    {
        return m_rect.height;
    }
    int getWidth()
    {
        return m_rect.width;
    }

    Rectangle collidingRect(CollisionBox box);
    Rectangle getRectangle();

private:
    Rectangle m_rect;
};
#endif