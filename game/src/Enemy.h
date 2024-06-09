

#ifndef ENEMEY_H
#define ENEMEY_H

#include "CharacterObject.h"

class Enemy : public CharacterObject
{
public:
    Enemy(const char *filePath, Vector2 initialPosition, std::string group);

    std::string m_group = "enemy";
};

#endif