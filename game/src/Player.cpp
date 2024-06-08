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
    CollisionBoxManager::GetInstance().AddCollisionBox("player", m_collisionBox);

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

void Player::move(float delta)
{

    getDirectionFromInput();
    float computedVelocityX = (m_velocity * delta) * m_direction.x;
    float computedVelocityY = (m_velocity * delta) * m_direction.y;

    Rectangle futurePosition = m_collisionBox->getRectangle();
    std::vector<CollisionBox *> boxes = filterOurOwnCollision(CollisionBoxManager::GetInstance().GetCollisionBoxesFor("player"));

    // std::cout << std::format("X Vel -> {}\n\n Yvel -> {}\n\n", computedVelocityX, computedVelocityY);

    futurePosition.x += computedVelocityX;
    for (auto &&collisionBox : boxes)
    {
        if (collisionBox->isCollidingWith(futurePosition))
        {
            if (computedVelocityX > 0.0f)
            {
                computedVelocityX = (collisionBox->m_position.x - m_collisionBox->m_width) - m_collisionBox->m_position.x;
            }
            else if (computedVelocityX < 0.0f)
            {
                computedVelocityX = (collisionBox->m_position.x + collisionBox->m_width) - m_collisionBox->m_position.x;
            }
        }
    }
    // Set future x position to rosolved posiion x
    futurePosition.x = m_collisionBox->getRectangle().x + computedVelocityX;

    futurePosition.y += computedVelocityY;
    for (auto &&collisionBox : boxes)
    {
        if (collisionBox->isCollidingWith(futurePosition))
        {
            if (computedVelocityY > 0.0f)
            {
                auto a = collisionBox->m_position.y - m_collisionBox->m_height;
                computedVelocityY = a - m_collisionBox->m_position.y;
            }
            else if (computedVelocityY < 0.0f)
            {
                computedVelocityY = (collisionBox->m_position.y + collisionBox->m_height) - m_collisionBox->m_position.y;
            }
            // Filter our selfs
        }
    }
    m_position.x += computedVelocityX;
    m_position.y += computedVelocityY;

    m_collisionBox->update(m_position);
}