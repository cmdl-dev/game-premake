
#include "raylib.h"
class CollisionBox
{
public:
    CollisionBox(Vector2 position, int width, int height);
    void draw();
    void update(Vector2 newPosition);

    bool isCollidingWith(CollisionBox box);
    bool isCollidingWith(Rectangle box);
    Rectangle collidingRect(CollisionBox box);

    int m_width;
    int m_height;
    Vector2 m_position;

    Rectangle getRectangle();

private:
};