

#include "raylib.h"
#include <string>
class Game
{

public:
    Game(int width, int height, std::string title);
    ~Game();

    void tick(float delta);
    void update(float delta);
    void draw();

    void handleEvents();

    bool shouldRunGame() { return WindowShouldClose(); };

private:
    int m_screenWidth;
    int m_screenHeight;
    // const int screenWidth = 800;
    // const int screenHeight = 450;
};