#include "Entity.h"
#include "EntityManager.h"
#include <format>

#include "imgui.h"

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

    {
        if (m_group == "player")
        {
            if (ImGui::CollapsingHeader(std::format("Entity {}", m_id).c_str()))
            {
                ImGui::SeparatorText("General");

                ImGui::Text(std::format("Group {}", m_group).c_str());
                ImGui::DragInt("Velocity", &m_velocity, 10, m_velocity - 50, m_velocity + 200);

                ImGui::SeparatorText("Position");
                ImGui::Text(std::format("Position: ({},{})", m_position->getPosition().x, m_position->getPosition().y).c_str());

                ImGui::SeparatorText("Health");
                ImGui::Text(std::format("Health: {}", m_health->getHealth()).c_str());

                ImGui::SeparatorText("Attack");
                ImGui::Text(std::format("Attack: {}", m_attack->getDamage()).c_str());

                ImGui::SeparatorText("Groups");
                std::string intGroup = "Interaction Groups: ";
                for (int i = 0; i < m_interactionGroups.size(); i++)
                {
                    intGroup += m_interactionGroups[i];

                    if (i != m_collisionGroups.size())
                    {
                        intGroup += ", ";
                    }
                }
                if (m_interactionGroups.size() == 0)
                {
                    intGroup += "None";
                }
                ImGui::Text(intGroup.c_str());

                ImGui::SeparatorText("Draw Hitboxes");

                // Showcase NOT relying on a IsItemHovered() to emit a tooltip.
                // Here the tooltip is always emitted when 'always_on == true'.
                int always_on = m_drawBoxLevels;
                ImGui::RadioButton("None", &always_on, 0);
                ImGui::SameLine();
                ImGui::RadioButton("Hitboxes", &always_on, 1);
                ImGui::SameLine();
                ImGui::RadioButton("HurtBoxes", &always_on, 2);
                ImGui::SameLine();
                ImGui::RadioButton("CollisionBoxes", &always_on, 3);
                ImGui::SameLine();
                ImGui::RadioButton("All", &always_on, 4);
                m_drawBoxLevels = (DrawBoxLevel)always_on;
                if (ImGui::TreeNode("Resize"))
                {

                    ImGui::SeparatorText("Resize Hitboxes");
                    int hitBoxSize_h = m_hitbox->getRect().height;
                    int hitBoxSize_w = m_hitbox->getRect().width;

                    ImGui::DragInt("Hitbox Width", &hitBoxSize_w, 1, 10, 100);
                    ImGui::DragInt("Hitbox Height", &hitBoxSize_h, 1, 10, 100);
                    m_hitbox->setRect(hitBoxSize_w, hitBoxSize_h);

                    ImGui::SeparatorText("Resize Hurtboxes");
                    int hurtBoxSize_h = m_hurtbox->getRect().height;
                    int hurtBoxSize_w = m_hurtbox->getRect().width;

                    ImGui::DragInt("Hurtbox Height", &hurtBoxSize_h, 1, 10, 100);
                    ImGui::DragInt("Hurtbox Width", &hurtBoxSize_w, 1, 10, 100);
                    m_hurtbox->setRect(hurtBoxSize_w, hurtBoxSize_h);

                    ImGui::SeparatorText("Resize Collisionboxes");
                    int collisionBoxSize_h = m_collisionBox->getRect().height;
                    int collisionBoxSize_w = m_collisionBox->getRect().width;

                    ImGui::DragInt("CollisionBox Height", &collisionBoxSize_h, 1, 10, 100);
                    ImGui::DragInt("CollisionBox Width", &collisionBoxSize_w, 1, 10, 100);
                    m_collisionBox->setRect(collisionBoxSize_w, collisionBoxSize_h);
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Animation"))
                {
                    ImGui::SeparatorText("Resize WOP");
                    float textureScale = m_animatedSprite->m_scale;
                    ImGui::DragFloat("Scale", &textureScale, 0.1f, 1, 5);
                    m_animatedSprite->resize(textureScale);

                    int animationSpeed = m_animatedSprite->getFrameSpeed();

                    ImGui::DragInt("Anmation Speed", &animationSpeed, 1, 1, 20);
                    m_animatedSprite->setFrameSpeed(animationSpeed);
                    ImGui::TreePop();
                }
            }
        }
    }
    m_animatedSprite->draw();

    m_hitbox->draw(m_drawBoxLevels == DrawBoxLevel::HIT || m_drawBoxLevels == DrawBoxLevel::ALL);
    m_hurtbox->draw(m_drawBoxLevels == DrawBoxLevel::HURT || m_drawBoxLevels == DrawBoxLevel::ALL);
    m_collisionBox->draw(m_drawBoxLevels == DrawBoxLevel::COLLISION || m_drawBoxLevels == DrawBoxLevel::ALL);

}; // Third;