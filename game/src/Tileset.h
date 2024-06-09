#ifndef TILESET_H
#define TILESET_H

#include "raylib.h"
#include "TileObject.h"

class Tileset
{

public:
    Tileset();
    ~Tileset();

    void loadMap(int arr[350]);
    void draw();

private:
    Texture2D m_grass;
    Texture2D m_dirt;

    TileObject *map[350];
};
#endif