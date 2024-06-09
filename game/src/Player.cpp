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

Player::Player(const char *filePath, AnimatedSpriteInfo spriteInfo, std::string group) : CharacterObject{filePath, spriteInfo, group}
{
    setCollisionGroup(std::vector<std::string>{"enemy", "dirt"});
    setVelocity(200);

    addAnimPosition("attackRight", AnimationInfo{Vector2{0, 0}, 4});
    setFrameSpeed(8);
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
    playAnimation("attackRight");
    getDirectionFromInput();
}