/**
 *
 * A character object is anything that can move
 *
 */
#ifndef CHARACTEROBJECT_H
#define CHARACTEROBJECT_H

#include "CollisionBoxManager.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"

class CharacterObject
{
public:
    CharacterObject(const char *filePath, Vector2 initialPosition, std::string group);

    CharacterObject(const char *filePath, AnimatedSpriteInfo spriteInfo, std::string group);

    void draw();
    void move(float delta);

    void setVelocity(int vel) { m_velocity = vel; }
    void setDirection(Vector2 newDirection) { m_direction = newDirection; };
    Vector2 getDirection() { return m_direction; };

    void setCollisionGroup(std::vector<std::string> vec) { m_collisionGroup = vec; };

    bool hasAnimations()
    {
        return m_animatedSprite != nullptr;
    };
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
    int m_velocity;

    Vector2 m_direction;
    Vector2 m_position;

    Texture2D m_texture;

    CollisionBox *m_collisionBox;
    SpriteAnimation *m_animatedSprite = nullptr;

    std::vector<std::string> m_collisionGroup;
    std::string m_group = std::string();

    Vector2 handleCollision(float delta);
    virtual void beforeMoveAction() {};
    void init(Vector2 position, Rectangle collisionRec, std::string group);
};

#endif