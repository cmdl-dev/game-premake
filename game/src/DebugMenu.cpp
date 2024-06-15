#include "DebugMenu.h"

#include "imgui.h"
#include "rlImGui.h"
#include "imgui_impl_raylib.h"
#include "DebugWindow.h"
#include "EntityManager.h"
#include <iostream>

// AnimationWindow AnimationViewer;
DebugMenu::DebugMenu()
{
    rlImGuiSetup(true);
    // AnimationViewer.Setup();
    // AnimationViewer.Open = true;
    m_animWindow = new AnimationWindow();
}

DebugMenu::~DebugMenu()
{
    rlImGuiShutdown();
    // ImGui_ImplRaylib_Shutdown();
    // ImGui::DestroyContext();
}

void DebugMenu::handleEvents()
{
    Vector2 pos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Rectangle mouseRect = Rectangle{pos.x, pos.y, 20, 20};
        std::vector<Entity *> allEntities = EntityManager::GetAllEntities();
        std::cout << "Checking " << allEntities.size() << "\n";
        for (Entity *e : allEntities)
        {
            if (e->isColliding(mouseRect))
            {
                if (m_selectedEntity != e)
                {
                    m_selectedEntity = e;

                    m_animWindow->Setup(m_selectedEntity->getAnimationTexture(), m_selectedEntity->getAnimatedSpriteInfo(), AnimationInfo{Vector2{0, 0}, 4, "play"}, 4);
                }
            }
        }
    }
    // ImGui_ImplRaylib_ProcessEvents();
}

void DebugMenu::newFrame()
{
    rlImGuiBegin();
    // ImGui_ImplRaylib_NewFrame();
    // ImGui::NewFrame();
}

void DebugMenu::update()
{

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    m_animWindow->Update();
    // AnimationViewer.Update();
    // ImGui::End();
}

void DebugMenu::draw()
{
    m_animWindow->Show();
    rlImGuiEnd();
}
