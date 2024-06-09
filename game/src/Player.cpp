#include "Player.h"

#include <format>
#include <iostream>

// TODO: Handle SCALE
const int PADDING = 10;
Player::Player(const char *filePath, Vector2 initialPosition, std::string group) : CharacterObject{filePath, initialPosition, group}
{
    setCollisionGroup(std::vector<std::string>{"enemy", "dirt"});
    setVelocity(200);
}

void Player::getDirectionFromInput()
{
    Vector2 newDir = Vector2{0, 0};
    if (IsKeyDown(KEY_U))
        newDir.x += 1;
    if (IsKeyDown(KEY_E))
        newDir.y += 1;
    if (IsKeyDown(KEY_O))
        newDir.x += -1;
    if (IsKeyDown(KEY_PERIOD))
        newDir.y += -1;

    setDirection(newDir);
}

void Player::beforeMoveAction()
{
    getDirectionFromInput();
}