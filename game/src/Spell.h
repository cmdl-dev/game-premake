#ifndef SPELL_H
#define SPELL_H

#include "SpriteAnimation.h"
#include "util/Types.h"
#include "TextureManager.h"
class Spell
{

public:
    Spell(const char *fileName, AnimatedSpriteInfo spriteInfo, PlayerDirection direction, int spellId);
    ~Spell() = default;

    void move(float delta);
    void update();
    void draw();
    void fire();
    void removeSpell();
    int getSpellId();
    bool isGCD() { return m_GCD > 0; }

    bool isDead();

private:
    int m_GCD = 100;
    int m_spellId = -1;
    int m_velocity = 300;
    int m_maxLife = 5 * 60;
    int m_life = 0;
    Vector2 m_position;
    Vector2 m_direction;
    SpriteAnimation *m_animatedSprite = nullptr;
};

#endif