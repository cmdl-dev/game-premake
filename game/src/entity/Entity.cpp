#include "Entity.h"

Entity::Entity(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows)
{
    Rectangle playerRect = Rectangle{initialPosition.x, initialPosition.y, texture.width / animationCols, texture.height / animationRows};

    m_animatedSprite = new SpriteAnimation(texture, AnimatedSpriteInfo{animationCols, animationRows, initialPosition});
    m_position = new PositionComponent(initialPosition);
    m_hitbox = new HitboxComponent(playerRect);
    m_collisionBox = new CollisionComponent(playerRect);

    m_health = new HealthComponent(100);

    CollisionBoxManager::AddCollisionBox(group, m_collisionBox);
    m_group = group;
}

void Entity::update(float delta)
{
    onBeforeUpdate(delta);
    // Move based on delta
    Vector2 calulatedVector = m_position->update(delta, m_velocity);
    Vector2 adjustedVector = Util::GetAdjustedVectorFromCollision(m_collisionBox, m_collisionGroups, calulatedVector);
    m_position->move(adjustedVector);

    // Have other things move too
    m_hitbox->move(m_position->getPosition());
    m_collisionBox->move(m_position->getPosition());
    m_animatedSprite->move(m_position->getPosition());
}

void Entity::draw()
{
    onBeforeDraw();

    m_hitbox->draw(m_drawBoxLevels == DrawBoxLevel::HITBOX || m_drawBoxLevels == DrawBoxLevel::BOTH);
    m_collisionBox->draw(m_drawBoxLevels == DrawBoxLevel::COLLISION || m_drawBoxLevels == DrawBoxLevel::BOTH);
    m_animatedSprite->draw();

}; // Third;
;
