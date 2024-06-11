

#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "SpriteAnimation.h"
#include "util/VectorUtil.h"
#include "util/Util.h"

#include "HitboxComponent.h"
#include "CollisionComponent.h"

class HealthComponent
{
public:
    HealthComponent(int health) { m_health = health; }
    void takeDamage(int dmg) { m_health -= dmg; };
    bool hasDied() { return m_health <= 0; };

private:
    int m_health;
};

class AttackComponent
{
public:
    AttackComponent(int attack) { m_damage = attack; };
    int getDamage() { return m_damage; };

private:
    int m_damage;
};

class PositionComponent
{
public:
    PositionComponent(Vector2 initialPosition) { m_position = initialPosition; }

    // Move is reserved for instance movement
    void setPosition(Vector2 pos) { m_position = pos; }
    void move(Vector2 pos)
    {
        m_position = VectorUtil::AddVector(m_position, pos);
    };
    void setDirection(Vector2 dir) { m_direction = dir; };

    Vector2 update(float delta, float velocity)
    {
        float c_VelocityX = (velocity * delta) * m_direction.x;
        float c_VelocityY = (velocity * delta) * m_direction.y;

        return Vector2{c_VelocityX, c_VelocityY};
    };
    Vector2 getPosition() { return m_position; };

private:
    Vector2 m_direction;
    Vector2 m_position;
};
enum DrawBoxLevel
{
    NONE,
    HITBOX,
    COLLISION,
    BOTH
};

class Entity
{
public:
    Entity(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows);

    void update(float delta);
    virtual void onBeforeUpdate(float delta) {};
    virtual void onBeforeDraw() {};
    void draw();

    void setVelocity(int vel) { m_velocity = vel; };
    void setCollisionGroups(std::vector<std::string> groups) { m_collisionGroups = groups; }

    Vector2 getPosition() { return m_position->getPosition(); }
    void setDirection(Vector2 vec) { m_position->setDirection(vec); }

    std::string getGroup() { return m_group; }

    void playAnimation(std::string name)
    {
        if (hasAnimations())
        {
            m_animatedSprite->play(name);
        }
    };
    void addAnimPosition(AnimationInfo info)
    {
        if (hasAnimations())
        {
            m_animatedSprite->addAnimationPositions(info);
        }
    };
    void setFrameSpeed(int speed)
    {
        if (hasAnimations())
        {
            m_animatedSprite->setFrameSpeed(speed);
        }
    }

    bool hasAnimations() { return m_animatedSprite != nullptr; };

private:
    std::string m_group;
    std::vector<std::string> m_collisionGroups;
    DrawBoxLevel m_drawBoxLevels = DrawBoxLevel::BOTH;
    int m_velocity = 100;
    /**AnimatedSprite
     *
     * This will handle the current position of the sprite
     *
     *  */
    SpriteAnimation *m_animatedSprite = nullptr;
    /**Position
     *
     * This will handle the current position of the sprite
     *
     *  */
    PositionComponent *m_position;

    /**Hitbox
     *
     * This will handle if this entity got hit
     *
     *
     * */
    HitboxComponent *m_hitbox;
    /**Health
     *
     * This will Handle the amount of hp and taking damage
     * */
    HealthComponent *m_health;
    /**Attack
     *
     * This will hold damage information
     *
     * */
    AttackComponent *m_attack;
    /** Collision
     *
     * This will handling if we should collide with another entity
     *
     *
     * */
    CollisionComponent *m_collisionBox;
};

#endif