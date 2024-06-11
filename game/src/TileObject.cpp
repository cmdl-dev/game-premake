#include "TileObject.h"
#include "HitboxManager.h"
#include "TextureManager.h"

TileObject::TileObject(std::string fileName, Rectangle rect, std::string group)
{
    m_texture = TextureManager::LoadTextureFromFile(fileName.c_str());
    m_rect = rect;
    m_collisionBox = new CollisionComponent(m_rect, Size{(float)m_texture.width, (float)m_texture.height + 10});
    m_group = group;

    HitboxManager::AddCollisionBox(m_group, m_collisionBox);
}

void TileObject::draw(bool drawBox)
{
    TextureManager::Draw(m_texture, Vector2{m_rect.x, m_rect.y});
    if (drawBox)
    {
        m_collisionBox->draw(drawBox);
    }
}

void TileObject::update(Vector2 newPosition)
{
    m_collisionBox->move(newPosition);

    m_rect.x = newPosition.x;
    m_rect.y = newPosition.y;
}
