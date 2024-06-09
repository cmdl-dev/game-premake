#include "CharacterObject.h"

// TODO: Handle SCALE
const int PADDING = 10;
CharacterObject::CharacterObject(const char *filePath, Vector2 initialPosition, std::string group)
{
    m_texture = TextureManager::LoadTextureFromFile(filePath);

    m_collisionBox = new CollisionBox(Rectangle{initialPosition.x, initialPosition.y, (float)m_texture.width + PADDING, (float)m_texture.height + PADDING});
    m_group = group;
    // m_collisionGroup = std::vector<std::string>{"enemy", "dirt"};

    if (m_group != std::string())
        CollisionBoxManager::AddCollisionBox(m_group, m_collisionBox);

    m_velocity = 200;
    m_direction = Vector2{0, 0};
    m_position = initialPosition;
}

void CharacterObject::draw()
{
    TextureManager::Draw(m_texture, m_position);
    m_collisionBox->draw();
}

Vector2 CharacterObject::handleCollision(float delta)
{
    // Calculated velocity
    float c_VelocityX = (m_velocity * delta) * m_direction.x;
    float c_VelocityY = (m_velocity * delta) * m_direction.y;

    Rectangle futurePosition = m_collisionBox->getRectangle();

    // TODO: Get only close tiles
    //  Filter our selfs
    std::vector<CollisionBox *> boxes = CollisionBoxManager::GetCollisionBoxesFor(m_collisionGroup);

    futurePosition.x += c_VelocityX;
    for (CollisionBox *collisionBox : boxes)
    {
        if (collisionBox->isCollidingWith(futurePosition))
        {
            if (c_VelocityX > 0.0f)
            {
                c_VelocityX = (collisionBox->getRectangle().x - m_collisionBox->getWidth()) - m_collisionBox->getRectangle().x;
            }
            else if (c_VelocityX < 0.0f)
            {
                c_VelocityX = (collisionBox->getRectangle().x + collisionBox->getWidth()) - m_collisionBox->getRectangle().x;
            }
        }
    }
    // Set future x position to rosolved posiion x
    futurePosition.x = m_collisionBox->getRectangle().x + c_VelocityX;

    futurePosition.y += c_VelocityY;
    for (CollisionBox *collisionBox : boxes)
    {
        if (collisionBox->isCollidingWith(futurePosition))
        {
            if (c_VelocityY > 0.0f)
            {
                c_VelocityY = (collisionBox->getRectangle().y - m_collisionBox->getHeight()) - m_collisionBox->getRectangle().y;
            }
            else if (c_VelocityY < 0.0f)
            {
                c_VelocityY = (collisionBox->getRectangle().y + collisionBox->getHeight()) - m_collisionBox->getRectangle().y;
            }
        }
    }
    return Vector2{c_VelocityX, c_VelocityY};
}
void CharacterObject::move(float delta)
{
    beforeMoveAction();
    // Computed X/Y
    Vector2 pos = handleCollision(delta);

    m_position.x += pos.x;
    m_position.y += pos.y;

    m_collisionBox->update(m_position);
}
