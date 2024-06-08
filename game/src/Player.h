
#include "raylib.h"

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
    Texture2D m_texture;

    void getDirectionFromInput();
};