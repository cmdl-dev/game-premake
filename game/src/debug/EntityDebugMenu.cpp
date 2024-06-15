#include "../EntityManager.h"
#include "EntityDebugMenu.h"
#include "imgui.h"

#include <format>

// TODO: When Spells get deleted we still hold their pointer
EntityDebugMenu::EntityDebugMenu()
{
}

void EntityDebugMenu::selectNewEntity(Entity *e)
{
    if (e != m_selectedEntity)
    {
        m_selectedEntity = e;
    }
}

void EntityDebugMenu::handleEvents()
{
    Vector2 pos = GetMousePosition();
    if (IsKeyDown(KEY_RIGHT_CONTROL) && IsKeyPressed(KEY_D))
    {
        toggleClicksEnabled();
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_clicksEnabled)
    {
        Rectangle mouseRect = Rectangle{pos.x, pos.y, 20, 20};
        std::vector<Entity *> allEntities = EntityManager::GetAllEntities();
        // std::cout << "Checking " << allEntities.size() << "\n";
        for (Entity *e : allEntities)
        {
            //
            // NOTE: Can possibly get a entity that has been deleted
            //
            if (e->isColliding(mouseRect))
            {
                if (m_selectedEntity != e && !m_lockSelectedEntity)
                {
                    lockEntity();
                    m_selectedEntity = e;
                    // m_animWindow->Setup(m_selectedEntity->getAnimationTexture(), m_selectedEntity->getAnimatedSpriteInfo(), AnimationInfo{Vector2{0, 0}, 4, "play"}, 4);
                }
            }
        }
    }
}

void EntityDebugMenu::update()
{
}

void EntityDebugMenu::show()
{

    if (m_clicksEnabled)
        showDebugBanner();

    if (m_selectedEntity)
    {
        {

            if (ImGui::Button(std::format("{}", m_lockSelectedEntity ? "Unlock" : "Lock").c_str()))
                toggleLockEntity();

            if (m_lockSelectedEntity)
            {
                ImGui::SameLine();
                ImGui::Text("Entity Selection is locked");
            }
        }

        if (ImGui::CollapsingHeader(std::format("Entity {} {}", m_selectedEntity->getGroup(), m_selectedEntity->getId()).c_str()))
        {
            if (ImGui::TreeNode("General"))
            {
                showGeneralSection();
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Hitboxes"))
            {
                showHitboxSection();
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Animation"))
            {
                showAnimationSection();
                ImGui::TreePop();
            }
            else
            {
                m_animationWindow.Shutdown();
            }
        }
    }
}

void EntityDebugMenu::showGeneralSection()
{
    ImGui::Text(std::format("Position: ({},{})", (int)m_selectedEntity->getPosition().x, (int)m_selectedEntity->getPosition().y).c_str());

    ImGui::Text(std::format("Health: {}", m_selectedEntity->getHealth()).c_str());

    ImGui::Text(std::format("Attack: {}", m_selectedEntity->getDamage()).c_str());
    int ent_velocity = m_selectedEntity->getVelocity();

    ImGui::DragInt("Velocity", &ent_velocity, 10, 50, 300);
    m_selectedEntity->setVelocity(ent_velocity);

    std::string intGroup = "Interaction Groups: ";
    for (int i = 0; i < m_selectedEntity->getInteractionGroups().size(); i++)
    {
        intGroup += m_selectedEntity->getInteractionGroups()[i];

        if (i != m_selectedEntity->getInteractionGroups().size() - 1)
        {
            intGroup += ", ";
        }
    }
    if (m_selectedEntity->getInteractionGroups().empty())
    {
        intGroup += "None";
    }
    ImGui::Text(intGroup.c_str());
}

void EntityDebugMenu::showHitboxSection()
{

    int ent_boxLevel = m_selectedEntity->getDrawBoxLevel();
    ImGui::RadioButton("None", &ent_boxLevel, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Hitboxes", &ent_boxLevel, 1);
    ImGui::SameLine();
    ImGui::RadioButton("HurtBoxes", &ent_boxLevel, 2);
    ImGui::SameLine();
    ImGui::RadioButton("CollisionBoxes", &ent_boxLevel, 3);
    ImGui::SameLine();
    ImGui::RadioButton("All", &ent_boxLevel, 4);

    m_selectedEntity->setDrawBoxLevel((DrawBoxLevel)ent_boxLevel);

    ImGui::SeparatorText("Resize Hitboxes");
    int hitBoxSize_h = m_selectedEntity->getHitboxRect().height;
    int hitBoxSize_w = m_selectedEntity->getHitboxRect().width;

    ImGui::DragInt("Hitbox Width", &hitBoxSize_w, 1, 10, 100);
    ImGui::DragInt("Hitbox Height", &hitBoxSize_h, 1, 10, 100);
    m_selectedEntity->setHitboxSize(hitBoxSize_w, hitBoxSize_h);

    ImGui::SeparatorText("Resize Hurtboxes");
    int hurtBoxSize_h = m_selectedEntity->getHurtboxRect().height;
    int hurtBoxSize_w = m_selectedEntity->getHurtboxRect().width;

    ImGui::DragInt("Hurtbox Height", &hurtBoxSize_h, 1, 10, 100);
    ImGui::DragInt("Hurtbox Width", &hurtBoxSize_w, 1, 10, 100);
    m_selectedEntity->setHurtboxSize(hurtBoxSize_w, hurtBoxSize_h);

    ImGui::SeparatorText("Resize Collisionboxes");
    int collisionBoxSize_h = m_selectedEntity->getCollisionboxRect().height;
    int collisionBoxSize_w = m_selectedEntity->getCollisionboxRect().width;

    ImGui::DragInt("CollisionBox Height", &collisionBoxSize_h, 1, 10, 100);
    ImGui::DragInt("CollisionBox Width", &collisionBoxSize_w, 1, 10, 100);
    m_selectedEntity->setCollisionBoxSize(collisionBoxSize_w, collisionBoxSize_h);
}

void EntityDebugMenu::showAnimationSection()
{
    if (ImGui::Button("View Animation"))
    {
        m_animationWindow.Setup(m_selectedEntity->getAnimationTexture(), m_selectedEntity->getAnimatedSpriteInfo(), m_selectedEntity->getCurrentAnimation(), 4);
    }
    ImGui::SameLine();
    if (ImGui::Button("Close Animation"))
    {
        m_animationWindow.Shutdown();
    }

    m_animationWindow.Update();
    m_animationWindow.Show();
}

void EntityDebugMenu::showDebugBanner()
{
    int boxHeight = 40;
    DrawRectangle(0, boxHeight, GetScreenWidth(), boxHeight, RED);
    int posX = GetScreenWidth() / 2 - MeasureText("COLLISION!", 20) / 2;
    int posY = boxHeight;
    DrawText("Debug Menu Enabled", posX, posY, 20, BLACK);
}