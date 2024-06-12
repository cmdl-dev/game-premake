#include "Spell.h"

Spell::Spell(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows, PlayerDirection direction, int spellId) : Entity{texture, initialPosition, group, animationCols, animationRows}
{
    // Texture2D texture, AnimatedSpriteInfo spriteInfo

    // m_animatedSprite = new SpriteAnimation(texture, spriteInfo);
    setInteractionGroups(std::vector<std::string>{"enemy"});

    m_spellId = spellId;

    // m_position = spriteInfo.pos;

    setAttack(50);
    addAnimPosition(AnimationInfo{Vector2{4, 0}, 4, "active"});
    setFrameSpeed(8);
    playAnimation("active");

    switch (direction)
    {
    case PlayerDirection::NORTH:
        setDirection(Vector2{0, -1});
        break;
    case PlayerDirection::EAST:
        setDirection(Vector2{1, 0});
        break;
    case PlayerDirection::SOUTH:
        setDirection(Vector2{0, 1});
        break;
    case PlayerDirection::WEST:
        setDirection(Vector2{-1, 0});
        break;
    default:
        setDirection(Vector2{1, 0});
        break;
    }
}

void Spell::onBeforeUpdate(float delta)
{
    if (isDead())
    {
        m_velocity = 0;
        return;
    }

    m_GCD--;
    m_life++;
}

void Spell::removeSpell()
{
    m_maxLife = -1;
}

int Spell::getSpellId()
{
    return m_spellId;
}

bool Spell::isDead()
{
    return m_life >= m_maxLife;
}
