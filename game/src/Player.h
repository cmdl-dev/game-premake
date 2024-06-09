#include "raylib.h"
#include "CollisionBoxManager.h"

class Player
{
public:
    Player(const char *filePath, Vector2 initialPosition);
    void draw();
    void move(float delta);

private:
    int m_velocity;
    Vector2 m_direction;
    Vector2 m_position;
    Vector2 m_lastGoodPosition;
    Texture2D m_texture;

    std::vector<CollisionBox *> filterOurOwnCollision(std::vector<CollisionBox *> arr);
    CollisionBox *m_collisionBox;

    void getDirectionFromInput();
    Vector2 handleCollisionVectors(float delta);
};