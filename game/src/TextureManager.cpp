#include "TextureManager.h"
#include <assert.h>

Texture2D TextureManager::LoadTextureFromFile(const char *fileName)
{
    Texture2D texture = LoadTexture(fileName);
    assert(texture.width != 0);

    return texture;
}

// TODO:
void TextureManager::Draw(Texture2D texture, Vector2 position)
{
    DrawTextureEx(texture, position, 0, 1.0f, WHITE);
}
