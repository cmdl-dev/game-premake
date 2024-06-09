#ifndef TILEOBJECT_H
#define TILEOBJECT_H

#include <string>
#include "TextureManager.h"
#include "CollisionBoxManager.h"

class TileObject
{
public:
    TileObject(std::string fileName, Rectangle position, std::string group);
    void draw(bool drawBox);
    void update(Vector2 newPosition);
    std::string getGroup() { return m_group; };

private:
    std::string m_group;
    Texture2D m_texture;
    Rectangle m_rect;
    CollisionBox *m_collisionBox;
};
#endif