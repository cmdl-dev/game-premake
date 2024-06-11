#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "entity/Entity.h"
#include "Spell.h"
#include "util/Types.h"
#include <vector>

// Entity(Texture2D texture, Vector2 intialPosition, std::string group, int animationCols, int animationRows);

class Player : public Entity
{
public:
    Player(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows);

    void fireSpell();

private:
    std::vector<Spell *> m_spellsArr;
    int m_spellCount = 0;

    PlayerDirection m_direction;
    PlayerState m_state;

    bool onGDC();
    void getAnimationFromState();
    void getDirectionFromInput();

    void onBeforeUpdate(float delta) override;
    void onBeforeDraw() override;

    // void beforeMoveAction(float delta) override;
    // void beforeDrawAction() override;

    void checkForDeadSpells();
    void removeDeadSpell(int spellId);
    void moveSpells(float delta);
    void drawSpells();

    int getSpellArraySize();
};

#endif