#include "Enemy.h"

Enemy::Enemy(const char *filePath, Vector2 initialPosition, std::string group) : CharacterObject{filePath, initialPosition, group}
{
    setCollisionGroup(std::vector<std::string>{"player", "dirt"});
    setVelocity(100);
}