#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "CharacterObject.h"
#include "Spell.h"
#include <vector>

// Bunny *bunnies = (Bunny *)malloc(MAX_BUNNIES*sizeof(Bunny));
class Player : public CharacterObject
{
public:
    Player(const char *filePath, Vector2 initialPosition, std::string group);
    Player(const char *filePath, AnimatedSpriteInfo spriteInfo, std::string group);

    void fireSpell();

private:
    std::vector<Spell *> m_spellsArr;
    int m_spellCount = 0;
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