#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "CharacterObject.h"

class Player : public CharacterObject
{
public:
    Player(const char *filePath, Vector2 initialPosition);

    void beforeMoveAction() override;

private:
    void getDirectionFromInput();
};

#endif