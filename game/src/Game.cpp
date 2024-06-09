#include "Game.h"

Player *player;
Enemy *enemy;
Tileset *map;
Vector2 pos = Vector2{0, 0};

Game::Game(int width, int height, std::string title)
{
    m_screenHeight = height;
    m_screenWidth = width;
    InitWindow(width, height, title.c_str());
    SetTraceLogLevel(LOG_ERROR);
    player = new Player("game/assets/enemy/Phoenix.png", Vector2{40, 40}, "player");

    enemy = new Enemy("game/assets/player/HealingTexture.png", Vector2{200, 200}, "enemy");

    map = new Tileset();
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
    map->draw();

    player->draw();
    enemy->draw();

    DrawFPS(20, 20);
    EndDrawing();
}
