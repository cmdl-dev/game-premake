

#ifndef ENEMEY_H
#define ENEMEY_H

#include "entity/Entity.h"

class Enemy : public Entity
{
public:
    Enemy(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows);
};

#endif