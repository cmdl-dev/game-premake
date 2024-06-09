#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#include "Player.h"
#include "Enemy.h"
#include "Tileset.h"

#include <string>
#include <vector>
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
};
#endif