#include "Tileset.h"
#include "TextureManager.h"
#include "CollisionBoxManager.h"
#include <iostream>

const int TILE_SIZE = 32;
const int SCREEN_HEIGHT = 450;
const int SCREEN_WIDTH = 800;

const int COLS = SCREEN_WIDTH / TILE_SIZE;
const int ROWS = SCREEN_HEIGHT / TILE_SIZE;

// clang-format off
int defaultLevel[COLS * ROWS] = {
  /*0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24*/
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};
// clang-format on

Tileset::Tileset()
{

    // m_grass = TextureManager::LoadTextureFromFile("game/assets/textures/grass.png");
    // m_dirt = TextureManager::LoadTextureFromFile("game/assets/textures/dirt.png");
    loadMap(defaultLevel);
}

void Tileset::loadMap(int arr[350])
{
    int type = 0;
    int row = 0;
    int col = 0;
    for (int i = 0; i < 350; i++)
    {
        type = arr[i];

        Rectangle rect = Rectangle{col * TILE_SIZE * 1.0f, row * TILE_SIZE * 1.0f, TILE_SIZE, TILE_SIZE};
        // std::cout << "( " << i << " ): " << "x: " << rect.x << " | y: " << rect.y << " | type: " << type << "\n";
        if (type == 0)
            map[i] = new TileObject("game/assets/textures/grass.png", rect, "grass");
        if (type == 1)
            map[i] = new TileObject("game/assets/textures/dirt.png", rect, "dirt");

        col++;
        if ((i + 1) % (COLS) == 0)
        {
            row++;
            col = 0;
        }
    }
}

void Tileset::draw()
{
    for (int i = 0; i < 350; i++)
    {
        map[i]->draw(map[i]->getGroup() == "dirt");
    }
}
