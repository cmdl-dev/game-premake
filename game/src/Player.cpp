#include "Player.h"
#include "TextureManager.h"

#include <format>
#include <iostream>

// TODO: Handle SCALE
const int PADDING = 10;
Player::Player(const char *filePath, Vector2 initialPosition)
{
    m_texture = TextureManager::LoadTextureFromFile(filePath);

    m_collisionBox = new CollisionBox(initialPosition, m_texture.width + PADDING, m_texture.height + PADDING);
    CollisionBoxManager::AddCollisionBox("player", m_collisionBox);

    m_velocity = 200;
    m_direction = Vector2{0, 0};
    m_position = initialPosition;
}

void Player::draw()
{
    TextureManager::Draw(m_texture, m_position);
    m_collisionBox->draw();
}

std::vector<CollisionBox *> Player::filterOurOwnCollision(std::vector<CollisionBox *> arr)
{
    std::vector<CollisionBox *> filtered;
    for (auto &&box : arr)
    {
        if (box != m_collisionBox)
            filtered.push_back(box);
    }
    return filtered;
}

void Player::getDirectionFromInput()
{
    m_direction = Vector2{0, 0};
    if (IsKeyDown(KEY_U))
        m_direction.x += 1;
    if (IsKeyDown(KEY_E))
        m_direction.y += 1;
    if (IsKeyDown(KEY_O))
        m_direction.x += -1;
    if (IsKeyDown(KEY_PERIOD))
        m_direction.y += -1;
}

Vector2 Player::handleCollisionVectors(float delta)
{
    float c_VelocityX = (m_velocity * delta) * m_direction.x;
    float c_VelocityY = (m_velocity * delta) * m_direction.y;

    Rectangle futurePosition = m_collisionBox->getRectangle();

    // Filter our selfs
    std::vector<CollisionBox *> boxes = filterOurOwnCollision(CollisionBoxManager::GetCollisionBoxesFor("player"));

    futurePosition.x += c_VelocityX;
    for (auto &&collisionBox : boxes)
    {
        if (collisionBox->isCollidingWith(futurePosition))
        {
            if (c_VelocityX > 0.0f)
            {
                c_VelocityX = (collisionBox->getPosition().x - m_collisionBox->getWidth()) - m_collisionBox->getPosition().x;
            }
            else if (c_VelocityX < 0.0f)
            {
                c_VelocityX = (collisionBox->getPosition().x + collisionBox->getWidth()) - m_collisionBox->getPosition().x;
            }
        }
    }
    // Set future x position to rosolved posiion x
    futurePosition.x = m_collisionBox->getRectangle().x + c_VelocityX;

    futurePosition.y += c_VelocityY;
    for (auto &&collisionBox : boxes)
    {
        if (collisionBox->isCollidingWith(futurePosition))
        {
            if (c_VelocityY > 0.0f)
            {
                c_VelocityY = (collisionBox->getPosition().y - m_collisionBox->getHeight()) - m_collisionBox->getPosition().y;
            }
            else if (c_VelocityY < 0.0f)
            {
                c_VelocityY = (collisionBox->getPosition().y + collisionBox->getHeight()) - m_collisionBox->getPosition().y;
            }
        }
    }
    return Vector2{c_VelocityX, c_VelocityY};
}

void Player::move(float delta)
{
    getDirectionFromInput();

    // Computed X/Y
    Vector2 pos = handleCollisionVectors(delta);

    m_position.x += pos.x;
    m_position.y += pos.y;

    m_collisionBox->update(m_position);
}