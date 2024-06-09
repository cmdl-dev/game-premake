#include "CollisionBox.h"

// TODO: Have the object centered around the box
CollisionBox::CollisionBox(Rectangle rect)
{
    m_rect = rect;
}

void CollisionBox::draw()
{
    DrawRectangleLines(m_rect.x, m_rect.y, m_rect.height, m_rect.width, RED);
}

void CollisionBox::update(Vector2 newPosition)
{
    m_rect.x = newPosition.x;
    m_rect.y = newPosition.y;
}

bool CollisionBox::isCollidingWith(Rectangle box)
{

    return CheckCollisionRecs(m_rect, box);
}

Rectangle CollisionBox::collidingRect(CollisionBox box)
{
    return GetCollisionRec(getRectangle(), box.getRectangle());
}

Rectangle CollisionBox::getRectangle()
{
    return m_rect;
}