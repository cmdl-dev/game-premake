#ifndef SPELL_H
#define SPELL_H

#include "util/Types.h"
#include "entity/Entity.h"

#include "SpriteAnimation.h"
#include "TextureManager.h"
class Spell : public Entity
{

public:
    Spell(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows, PlayerDirection direction, int spellId);
    ~Spell() = default;

    void onBeforeUpdate(float delta) override;
    void removeSpell();

    bool isGCD() { return m_GCD > 0; }
    bool isDead();

    int getSpellId();

private:
    int m_GCD = 100;
    int m_spellId = -1;
    int m_velocity = 300;
    int m_maxLife = 5 * 60;
    int m_life = 0;
    SpriteAnimation *m_animatedSprite = nullptr;
};

#endif