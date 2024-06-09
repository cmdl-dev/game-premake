
#include "raylib.h"
class CollisionBox
{
public:
    CollisionBox(Vector2 position, int width, int height);
    void draw();
    void update(Vector2 newPosition);

    bool isCollidingWith(CollisionBox box);
    bool isCollidingWith(Rectangle box);

    int getHeight()
    {
        return m_height;
    }
    int getWidth()
    {
        return m_width;
    }
    Vector2 getPosition()
    {
        return m_position;
    }

    Rectangle collidingRect(CollisionBox box);

    Rectangle getRectangle();

private:
    int m_width;
    int m_height;
    Vector2 m_position;
};