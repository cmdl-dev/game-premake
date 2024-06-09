#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "raylib.h"

class TextureManager
{
public:
    static Texture2D LoadTextureFromFile(const char *fileName);
    static void Draw(Texture2D texture, Vector2 position);
};

#endif