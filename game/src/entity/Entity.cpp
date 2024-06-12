#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows)
{
    m_id = Util::UniqueId::getUniqueId();

    m_group = group;
    Rectangle playerRect = Rectangle{initialPosition.x, initialPosition.y, texture.width / animationCols, texture.height / animationRows};

    m_animatedSprite = new SpriteAnimation(texture, AnimatedSpriteInfo{animationCols, animationRows, initialPosition});

    m_hitbox = new HitboxComponent(playerRect, Size{playerRect.width, playerRect.height}, m_id);
    m_hurtbox = new HurtboxComponent(playerRect, Size{playerRect.width, playerRect.height}, m_id);
    m_collisionBox = new CollisionComponent(playerRect, Size{playerRect.width, playerRect.height}, m_id);

    m_position = new PositionComponent(initialPosition);
    m_attack = new AttackComponent(10);
    m_health = new HealthComponent(100);

    HitboxManager::AddCollisionBox(group, m_collisionBox);
    EntityManager::AddEntities(group, this);
}

void Entity::update(float delta)
{
    onBeforeUpdate(delta);
    // Move based on delta
    Vector2 calulatedVector = m_position->update(delta, m_velocity);
    Vector2 adjustedVector = Util::GetAdjustedVectorFromCollision(m_collisionBox, m_collisionGroups, calulatedVector);

    // TODO: Refactor to have this be an array of entities with different functions for each types
    std::vector<Entity *> entities = EntityManager::GetEntitiesFor(m_interactionGroups);
    for (Entity *ent : entities)
    {
        if (m_hurtbox->didCollideWith(ent->m_hitbox->getRect()) && !m_tookHitFrom[ent->getId()])
        {
            m_hurtbox->onCollision(ent->m_health, m_attack->getDamage());
        }
        m_tookHitFrom[ent->getId()] = m_hurtbox->didCollideWith(ent->m_hitbox->getRect());
    }

    m_position->move(adjustedVector);

    // Have other things move too
    m_hitbox->move(m_position->getPosition());
    m_hurtbox->move(m_position->getPosition());

    m_collisionBox->move(m_position->getPosition());
    m_animatedSprite->move(m_position->getPosition());
}

void Entity::draw()
{
    onBeforeDraw();

    m_animatedSprite->draw();

    m_hitbox->draw(m_drawBoxLevels == DrawBoxLevel::HIT || m_drawBoxLevels == DrawBoxLevel::ALL);
    m_hurtbox->draw(m_drawBoxLevels == DrawBoxLevel::HURT || m_drawBoxLevels == DrawBoxLevel::ALL);
    m_collisionBox->draw(m_drawBoxLevels == DrawBoxLevel::COLLISION || m_drawBoxLevels == DrawBoxLevel::ALL);

}; // Third;