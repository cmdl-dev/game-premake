/**
 *
 * A character object is anything that can move
 *
 */
#ifndef CHARACTEROBJECT_H
#define CHARACTEROBJECT_H

#include "CollisionBoxManager.h"
#include "TextureManager.h"

class CharacterObject
{
public:
    CharacterObject(const char *filePath, Vector2 initialPosition, std::string group);

    void draw();
    void move(float delta);

    void setVelocity(int vel) { m_velocity = vel; }
    void setDirection(Vector2 newDirection) { m_direction = newDirection; };

    void setCollisionGroup(std::vector<std::string> vec) { m_collisionGroup = vec; };

private:
    int m_velocity;

    Vector2 m_direction;
    Vector2 m_position;

    Texture2D m_texture;

    CollisionBox *m_collisionBox;

    std::vector<std::string> m_collisionGroup;
    std::string m_group = std::string();

    Vector2 handleCollision(float delta);
    virtual void beforeMoveAction() {};
};

#endif