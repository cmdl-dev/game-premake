#include "Game.h"
#include "Player.h"

Texture2D tex;
Player *player;
Vector2 pos = Vector2{0, 0};

Game::Game(int width, int height, std::string title)
{
    m_screenHeight = height;
    m_screenWidth = width;
    InitWindow(width, height, title.c_str());
    player = new Player("game/assets/enemy/Phoenix.png", Vector2{0, 0});
}
Game::~Game()
{
    CloseWindow();
}
void Game::tick(float delta)
{
    update(delta);
    draw();
}

void Game::update(float delta)
{
    player->move(delta);
}
void Game::handleEvents()
{
    // getDirection();
}
void Game::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    player->draw();
    EndDrawing();
}
