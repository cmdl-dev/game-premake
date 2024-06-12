#include "Entity.h"

Entity::Entity(Texture2D texture, Vector2 initialPosition, std::string group, int animationCols, int animationRows)
{
    m_group = group;
    Rectangle playerRect = Rectangle{initialPosition.x, initialPosition.y, texture.width / animationCols, texture.height / animationRows};

    m_animatedSprite = new SpriteAnimation(texture, AnimatedSpriteInfo{animationCols, animationRows, initialPosition});

    m_hitbox = new HitboxComponent(playerRect, Size{playerRect.width, playerRect.height});
    m_hurtbox = new HurtboxComponent(playerRect, Size{playerRect.width, playerRect.height});
    m_collisionBox = new CollisionComponent(playerRect, Size{playerRect.width, playerRect.height});

    m_position = new PositionComponent(initialPosition);
    m_attack = new AttackComponent(10);
    m_health = new HealthComponent(100);

    HitboxManager::AddCollisionBox(group, m_collisionBox);
    HitboxManager::AddCollisionBox("hit_hurt_" + group, m_hitbox);
}

void Entity::update(float delta)
{
    onBeforeUpdate(delta);
    // Move based on delta
    Vector2 calulatedVector = m_position->update(delta, m_velocity);
    Vector2 adjustedVector = Util::GetAdjustedVectorFromCollision(m_collisionBox, m_collisionGroups, calulatedVector);

    std::vector<Hitbox *> boxes = HitboxManager::GetCollisionBoxesFor(m_interactionGroups);
    for (Hitbox *hitbox : boxes)
    {
        if (m_hurtbox->didCollideWith(hitbox->getRect()))
        {
            m_hurtbox->onCollision(m_health, m_attack->getDamage());
        }
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