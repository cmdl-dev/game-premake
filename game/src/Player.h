#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "CharacterObject.h"

class Player : public CharacterObject
{
public:
    Player(const char *filePath, Vector2 initialPosition, std::string group);

private:
    void getDirectionFromInput();
    void beforeMoveAction() override;
};

#endif