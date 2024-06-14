#include "DebugMenu.h"

#include "imgui.h"
#include "rlImGui.h"
#include "imgui_impl_raylib.h"
#include "DebugWindow.h"

AnimationWindow AnimationViewer;
DebugMenu::DebugMenu()
{
    rlImGuiSetup(true);
    AnimationViewer.Setup();
    AnimationViewer.Open = true;
}

DebugMenu::~DebugMenu()
{
    rlImGuiShutdown();
    // ImGui_ImplRaylib_Shutdown();
    // ImGui::DestroyContext();
}

void DebugMenu::handleEvents()
{
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
    AnimationViewer.Update();
    // ImGui::End();
}

void DebugMenu::draw()
{
    AnimationViewer.Show();
    rlImGuiEnd();
}
