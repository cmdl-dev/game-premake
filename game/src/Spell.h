#ifndef SPELL_H
#define SPELL_H

#include "SpriteAnimation.h"
#include "TextureManager.h"

class Spell
{

public:
    Spell(const char *fileName, AnimatedSpriteInfo spriteInfo, int spellId);
    ~Spell() = default;

    void move(float delta);
    void update();
    void draw();
    void fire();
    void removeSpell();
    int getSpellId();

    bool isDead();

private:
    int m_spellId = -1;
    int m_velocity = 50;
    int m_maxLife = 10 * 60;
    int m_life = 0;
    Vector2 m_position;
    Vector2 m_direction;
    SpriteAnimation *m_animatedSprite = nullptr;
};

#endif