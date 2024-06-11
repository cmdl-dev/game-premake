#include "Enemy.h"

Enemy::Enemy(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows) : Entity{texture, initialPosition, group, animationCols, animationRows}
{
    setCollisionGroups(std::vector<std::string>{"player", "dirt"});
    setVelocity(100);
}