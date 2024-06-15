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
    m_EntDebugMenu = new EntityDebugMenu();
    // m_animWindow = new AnimationWindow();
}

DebugMenu::~DebugMenu()
{
    rlImGuiShutdown();
    // ImGui_ImplRaylib_Shutdown();
    // ImGui::DestroyContext();
}

void DebugMenu::handleEvents()
{
    m_EntDebugMenu->handleEvents();
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
    m_EntDebugMenu->update();
    // m_animWindow->Update();
    // AnimationViewer.Update();
    // ImGui::End();
}

void DebugMenu::draw()
{
    m_EntDebugMenu->show();
    // m_animWindow->Show();
    rlImGuiEnd();
}
