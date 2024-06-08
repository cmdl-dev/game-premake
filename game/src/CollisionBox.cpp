#include "CollisionBox.h"

// TODO: Have the object centered around the box
CollisionBox::CollisionBox(Vector2 position, int width, int height)
{
    m_position = position;
    m_width = width;
    m_height = height;
}

void CollisionBox::draw()
{
    DrawRectangleLines(m_position.x, m_position.y, m_width, m_height, RED);
}

void CollisionBox::update(Vector2 newPosition)
{
    m_position = newPosition;
}

bool CollisionBox::isCollidingWith(CollisionBox box)
{
    return CheckCollisionRecs(getRectangle(), box.getRectangle());
}

bool CollisionBox::isCollidingWith(Rectangle box)
{

    return CheckCollisionRecs(getRectangle(), box);
}

Rectangle CollisionBox::collidingRect(CollisionBox box)
{
    return GetCollisionRec(getRectangle(), box.getRectangle());
}

Rectangle CollisionBox::getRectangle()
{
    return Rectangle{m_position.x, m_position.y, m_width * 1.0f, m_height * 1.0f};
}