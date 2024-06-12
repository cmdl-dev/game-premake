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
    if (ImGui::CollapsingHeader("Inputs & Focus"))
    {
        {

            ImGui::SeparatorText("ABOUT THIS DEMO:");
            ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
            ImGui::BulletText("The \"Examples\" menu above leads to more demo contents.");
            ImGui::BulletText("The \"Tools\" menu above gives access to: About Box, Style Editor,\n"
                              "and Metrics/Debugger (general purpose Dear ImGui debugging tool).");

            ImGui::SeparatorText("PROGRAMMER GUIDE:");
            ImGui::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
            ImGui::BulletText("See comments in imgui.cpp.");
            ImGui::BulletText("See example applications in the examples/ folder.");
            ImGui::BulletText("Read the FAQ at https://www.dearimgui.com/faq/");
            ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
            ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");

            ImGui::SeparatorText("USER GUIDE:");
        }
    }
    // ImGui::End();
}

void DebugMenu::draw()
{
    rlImGuiEnd();
    // ImGui::Render();
    // ImGui_ImplRaylib_RenderDrawData(ImGui::GetDrawData());
}
