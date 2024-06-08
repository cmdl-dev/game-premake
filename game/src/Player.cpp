#include "Player.h"
#include "TextureManager.h"
#include <iostream>

Player::Player(const char *filePath, Vector2 initialPosition)
{
    m_texture = TextureManager::LoadTextureFromFile(filePath);
    m_velocity = 200;
    m_direction = Vector2{0, 0};
    m_position = initialPosition;
}

void Player::draw()
{
    TextureManager::Draw(m_texture, m_position);
}

void Player::getDirectionFromInput()
{
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
    m_position.x = (m_velocity * delta) * m_direction.x;
    m_position.y = (m_velocity * delta) * m_direction.y;
}
