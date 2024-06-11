#include "Spell.h"

Spell::Spell(const char *fileName, AnimatedSpriteInfo spriteInfo, PlayerDirection direction, int spellId)
{
    // Texture2D texture, AnimatedSpriteInfo spriteInfo
    Texture2D texture = TextureManager::LoadTextureFromFile(fileName);

    m_animatedSprite = new SpriteAnimation(texture, spriteInfo);

    m_spellId = spellId;

    m_position = spriteInfo.pos;
    m_animatedSprite->addAnimationPositions(AnimationInfo{Vector2{4, 0}, 4, "active"});
    m_animatedSprite->setFrameSpeed(8);
    m_animatedSprite->play("active");

    switch (direction)
    {
    case PlayerDirection::NORTH:

        m_direction = Vector2{0, -1};
        break;

    case PlayerDirection::EAST:
        m_direction = Vector2{1, 0};
        break;
    case PlayerDirection::SOUTH:
        m_direction = Vector2{0, 1};
        break;
    case PlayerDirection::WEST:
        m_direction = Vector2{-1, 0};
        break;
    default:
        m_direction = Vector2{1, 0};
        break;
    }
}

void Spell::move(float delta)
{
    if (isDead())
    {
        m_position.y = -1;
        m_position.x = -1;
        m_velocity = 0;
        return;
    }

    m_position.x += (m_velocity * delta) * m_direction.x;
    m_position.y += (m_velocity * delta) * m_direction.y;

    m_animatedSprite->move(m_position);
    m_GCD--;
    m_life++;
}

void Spell::update()
{
    // TODO: change

    // m_direction = Vector2{1, 0};
}

void Spell::draw()
{
    m_animatedSprite->draw();
}

void Spell::fire()
{
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
