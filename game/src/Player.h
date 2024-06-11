#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "CharacterObject.h"
#include "Spell.h"
#include "util/Types.h"
#include <vector>

class Player : public CharacterObject
{
public:
    Player(const char *filePath, Vector2 initialPosition, std::string group);
    Player(const char *filePath, AnimatedSpriteInfo spriteInfo, std::string group);

    void fireSpell();

private:
    std::vector<Spell *> m_spellsArr;
    int m_spellCount = 0;

    PlayerDirection m_direction;
    PlayerState m_state;

    bool onGDC();
    void getAnimationFromState();
    void getDirectionFromInput();
    void beforeMoveAction(float delta) override;
    void beforeDrawAction() override;

    void checkForDeadSpells();
    void removeDeadSpell(int spellId);
    void moveSpells(float delta);
    void drawSpells();

    int getSpellArraySize();
};

#endif