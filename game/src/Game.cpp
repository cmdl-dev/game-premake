#include "Game.h"

Texture2D tex;
Player *player;
Player *enemy;
Tileset *map;
Vector2 pos = Vector2{0, 0};

Game::Game(int width, int height, std::string title)
{
    m_screenHeight = height;
    m_screenWidth = width;
    InitWindow(width, height, title.c_str());
    SetTraceLogLevel(LOG_ERROR);
    player = new Player("game/assets/enemy/Phoenix.png", Vector2{40, 40});

    // CollisionBoxManager::
    enemy = new Player("game/assets/player/HealingTexture.png", Vector2{100, 100});

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
    // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    player->draw();
    enemy->draw();

    DrawFPS(20, 20);
    EndDrawing();
}
