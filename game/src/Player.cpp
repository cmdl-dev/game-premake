#include "Player.h"

#include <iostream>

// TODO: Handle SCALE
const int PADDING = 10;
Player::Player(const char *filePath, Vector2 initialPosition, std::string group) : CharacterObject{filePath, initialPosition, group}
{
    setCollisionGroup(std::vector<std::string>{"enemy", "dirt"});
    setVelocity(50);
}

Player::Player(const char *filePath, AnimatedSpriteInfo spriteInfo, std::string group) : CharacterObject{filePath, spriteInfo, group}
{
    setCollisionGroup(std::vector<std::string>{"enemy", "dirt"});
    setVelocity(100);

    addAnimPosition(AnimationInfo{Vector2{0, 0}, 4, "idle"});
    addAnimPosition(AnimationInfo{Vector2{0, 4}, 4, "walk_e"});
    addAnimPosition(AnimationInfo{Vector2{0, 5}, 4, "walk_w"});
    addAnimPosition(AnimationInfo{Vector2{0, 6}, 4, "walk_s"});
    addAnimPosition(AnimationInfo{Vector2{0, 7}, 4, "walk_n"});
    setFrameSpeed(4);
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

    Vector2 dir = getDirection();

    if (dir.x == 1)
        playAnimation("walk_e");
    if (dir.x == -1)
        playAnimation("walk_w");

    if (dir.y == -1)
        playAnimation("walk_n");
    if (dir.y == 1)
        playAnimation("walk_s");

    if (dir.x == 0 && dir.y == 0)
        playAnimation("idle");
}