#include "TextureManager.h"

Texture2D TextureManager::LoadTextureFromFile(const char *fileName)
{
    Texture2D texture = LoadTexture(fileName);
    return texture;
}

// TODO:
void TextureManager::Draw(Texture2D texture, Vector2 position)
{
    DrawTextureEx(texture, position, 0, 2.0f, WHITE);
}
