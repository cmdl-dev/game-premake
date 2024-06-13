#include "Player.h"
#include "util/VectorUtil.h"

#include <format>
#include <iostream>

// TODO: Handle SCALE
const int PADDING = 10;

Player::Player(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows) : Entity{texture, initialPosition, group, animationCols, animationRows}
{
    setCollisionGroups(std::vector<std::string>{"dirt"});
    // setInteractionGroups(std::vector<std::string>{"enemy"});

    setVelocity(100);

    addAnimPosition(AnimationInfo{Vector2{0, 0}, 4, "idle_e"});
    addAnimPosition(AnimationInfo{Vector2{0, 1}, 4, "idle_w"});
    addAnimPosition(AnimationInfo{Vector2{0, 2}, 4, "idle_s"});
    addAnimPosition(AnimationInfo{Vector2{0, 3}, 4, "idle_n"});

    addAnimPosition(AnimationInfo{Vector2{0, 4}, 4, "walk_e"});
    addAnimPosition(AnimationInfo{Vector2{0, 5}, 4, "walk_w"});
    addAnimPosition(AnimationInfo{Vector2{0, 6}, 4, "walk_s"});
    addAnimPosition(AnimationInfo{Vector2{0, 7}, 4, "walk_n"});
    setFrameSpeed(4);

    m_spellsArr.reserve(2000);

    setHitboxCenter(true);
    setCollisionBoxCenter(true);

    setCollisionBoxSize(20, 20);
    setHurtboxSize(60, 60);
    setHitboxSize(40, 40);
}

void Player::fireSpell()
{
    if (getSpellArraySize() >= 100)
        return;

    m_spellsArr.push_back(new Spell(TextureManager::LoadTextureFromFile("game/assets/textures/lightningBallEffect.png"), getPosition(), "spells", 16, 1, m_direction, getSpellArraySize()));
}

void Player::getAnimationFromState()
{
    if (m_state == PlayerState::IDLE)
    {
        switch (m_direction)
        {
        case PlayerDirection::NORTH:
            playAnimation("idle_n");
            /* code */
            break;

        case PlayerDirection::EAST:
            playAnimation("idle_e");
            /* code */
            break;
        case PlayerDirection::SOUTH:
            playAnimation("idle_s");
            /* code */
            break;
        case PlayerDirection::WEST:
            /* code */
            playAnimation("idle_w");
            break;
        default:
            playAnimation("idle_e");
            break;
        }
    }
    if (m_state == PlayerState::MOVING)
    {

        switch (m_direction)
        {
        case PlayerDirection::NORTH:
            playAnimation("walk_n");
            /* code */
            break;

        case PlayerDirection::EAST:
            playAnimation("walk_e");
            /* code */
            break;
        case PlayerDirection::SOUTH:
            playAnimation("walk_s");
            /* code */
            break;
        case PlayerDirection::WEST:
            /* code */
            playAnimation("walk_w");
            break;
        default:
            playAnimation("idle_e");
            break;
        }
    }
}

void Player::getDirectionFromInput()
{
    m_state = PlayerState::IDLE;
    Vector2 newDir = Vector2{0, 0};
    if (IsKeyDown(KEY_U))
        newDir.x += 1;
    if (IsKeyDown(KEY_E))
        newDir.y += 1;
    if (IsKeyDown(KEY_O))
        newDir.x += -1;
    if (IsKeyDown(KEY_PERIOD))
        newDir.y += -1;

    if (!VectorUtil::VectorEqual(newDir, Vector2{0, 0}))
    {
        m_state = PlayerState::MOVING;
    }

    if (VectorUtil::VectorEqual(newDir, Vector2{0, -1}))
        m_direction = PlayerDirection::NORTH;

    if (VectorUtil::VectorEqual(newDir, Vector2{1, 0}))
        m_direction = PlayerDirection::EAST;

    if (VectorUtil::VectorEqual(newDir, Vector2{0, 1}))
        m_direction = PlayerDirection::SOUTH;

    if (VectorUtil::VectorEqual(newDir, Vector2{-1, 0}))
        m_direction = PlayerDirection::WEST;

    setDirection(newDir);
}

void Player::onBeforeUpdate(float delta)
{
    getDirectionFromInput();
    getAnimationFromState();

    // REFACTOR THIS
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !onGDC())
    {
        m_state = PlayerState::ATTACKING;
    }

    if (m_state == PlayerState::ATTACKING)
    {
        m_state == PlayerState::IDLE;
        checkForDeadSpells();
        fireSpell();
    }

    moveSpells(delta);
}

void Player::onBeforeDraw()
{
    {
        // static int speed = 2;

        // ImGui::SliderInt("Size", &speed, 3, 10);
        // setFrameSpeed(speed);
    }
    drawSpells();
}

void Player::checkForDeadSpells()
{
    for (auto &&spell : m_spellsArr)
    {
        if (spell->isDead())
        {
            removeDeadSpell(spell->getSpellId());
        }
    }
}

void Player::removeDeadSpell(int spellId)
{
    for (int i = 0; i < m_spellsArr.size(); i++)
    {
        Spell *spell = m_spellsArr[i];
        if (spell->getSpellId() == spellId)
        {
            spell->removeSpell();
            delete spell;
            m_spellsArr.erase(m_spellsArr.begin() + i);
        }
    }
}
bool Player::onGDC()
{
    for (int i = 0; i < getSpellArraySize(); i++)
    {
        Spell *spell = m_spellsArr[i];
        if (spell->isGCD())
            return true;
    }
    return false;
}

void Player::moveSpells(float delta)
{
    for (int i = 0; i < getSpellArraySize(); i++)
    {
        Spell *spell = m_spellsArr[i];
        if (!spell->isDead())
        {
            spell->update(delta);
        }
    }
}

void Player::drawSpells()
{
    for (int i = 0; i < getSpellArraySize(); i++)
    {
        Spell *spell = m_spellsArr[i];
        if (!spell->isDead())
        {
            spell->draw();
        }
    }
}

int Player::getSpellArraySize()
{
    return m_spellsArr.size();
}
