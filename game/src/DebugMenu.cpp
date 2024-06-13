#include "DebugMenu.h"

#include "imgui.h"
#include "rlImGui.h"
#include "imgui_impl_raylib.h"

DebugMenu::DebugMenu()
{

    rlImGuiSetup(true);
    // ImGui::CreateContext();
    // ImGuiIO &io = ImGui::GetIO();
    // (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // ImGui::StyleColorsDark();
    // ImGui_ImplRaylib_Init();

    // io.Fonts->AddFontDefault();
    // ImFont *font = io.Fonts->AddFontFromFileTTF("game/resources/driusstraight.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    // IM_ASSERT(font != nullptr);
    // // required to be called to cache the font texture with raylib
    // Imgui_ImplRaylib_BuildFontAtlas();
}

DebugMenu::~DebugMenu()
{
    rlImGuiShutdown();
    // ImGui_ImplRaylib_Shutdown();
    // ImGui::DestroyContext();
}

void DebugMenu::handleEvents()
{
    rlImGuiBegin();
    // ImGui_ImplRaylib_ProcessEvents();
}

void DebugMenu::newFrame()
{
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
    // ImGui::End();
}

void DebugMenu::draw()
{
    rlImGuiEnd();
    // ImGui::Render();
    // ImGui_ImplRaylib_RenderDrawData(ImGui::GetDrawData());
}
