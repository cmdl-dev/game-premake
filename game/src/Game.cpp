#include "Game.h"

Player *player;
// Enemy *enemy;
Tileset *map;
Vector2 pos = Vector2{0, 0};

Game::Game(int width, int height, std::string title)
{
    m_screenHeight = height;
    m_screenWidth = width;
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

    InitWindow(width, height, title.c_str());
    SetTraceLogLevel(LOG_ERROR);
    Texture2D playerTextures = TextureManager::LoadTextureFromFile("game/assets/player/Heavy_Knight_Non-Combat_Animations.png", 3.0);
    // Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows
    player = new Player(playerTextures, Vector2{100, 100}, "player", 4, 31);
    // enemy = new Enemy("game/assets/player/HealingTexture.png", Vector2{200, 200}, "enemy");

    map = new Tileset();

    rlImGuiSetup(true);
}
Game::~Game()
{
    CloseWindow();
    rlImGuiShutdown();
}
// 2nd
void Game::tick(float delta)
{
    update(delta);
    draw();
}
void Game::update(float delta)
{
    player->update(delta);
    // player->move(delta);
}
// 1st
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
    // enemy->draw();

    {
        rlImGuiBegin();
        bool open = true;
        ImGui::ShowDemoWindow(&open);
        rlImGuiEnd();
    }
    DrawFPS(20, 20);
    EndDrawing();
}
