

#ifndef ENTITY_H
#define ENTITY_H
#include <cstdint>

#include "raylib.h"
#include "SpriteAnimation.h"
#include "util/VectorUtil.h"
#include "util/Util.h"

#include "HealthComponent.h"
#include "HitboxComponent.h"
#include "HurtboxComponent.h"
#include "CollisionComponent.h"

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
    HIT,
    HURT,
    COLLISION,
    ALL
};

class Entity
{
public:
    Entity(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows);

    void update(float delta);
    void draw();
    void setVelocity(int vel) { m_velocity = vel; };
    void setCollisionGroups(std::vector<std::string> groups) { m_collisionGroups = groups; }
    void setInteractionGroups(std::vector<std::string> groups)
    {
        std::vector<std::string> arr;
        for (int i = 0; i < groups.size(); i++)
        {
            arr.push_back("hit_hurt_" + groups[i]);
        }
        m_interactionGroups = arr;
    }
    virtual void onBeforeUpdate(float delta) {};
    virtual void onBeforeDraw() {};
    std::string getGroup() { return m_group; }

    void setHitboxSize(float width, float height) { m_hitbox->setRect(width, height); };
    void setHurtboxSize(float width, float height) { m_hurtbox->setRect(width, height); };
    void setCollisionBoxSize(float width, float height) { m_collisionBox->setRect(width, height); };

    void setHurtboxCenter(bool center) { m_hurtbox->setCentered(center); }
    void setHitboxCenter(bool center) { m_hitbox->setCentered(center); }
    void setCollisionBoxCenter(bool center) { m_collisionBox->setCentered(center); }

    void setDirection(Vector2 vec) { m_position->setDirection(vec); }
    Vector2 getPosition() { return m_position->getPosition(); }

    bool hasAnimations() { return m_animatedSprite != nullptr; };
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

private:
    uint32_t m_id;

    std::map<uint32_t, bool> m_tookHitFrom;
    std::string m_group;
    std::vector<std::string> m_collisionGroups;   // This will manage if you collide with another object
    std::vector<std::string> m_interactionGroups; // This will manage if you interact with another hitbox
    DrawBoxLevel m_drawBoxLevels = DrawBoxLevel::ALL;
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

    /**Hitbox and Hurtbox
     *
     * If a hitbox collides with a hurt box then the hurt box takes tamage
     *
     *
     * */
    HitboxComponent *m_hitbox;

    HurtboxComponent *m_hurtbox;
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