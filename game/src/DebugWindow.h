#ifndef DOCUMENTWINDOW_H
#define DOCUMENTWINDOW_H
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "SpriteAnimation.h"
#include "TextureManager.h"

class DocumentWindow
{
public:
    bool Open = false;

    RenderTexture ViewTexture;

    virtual void Setup() = 0;
    virtual void Shutdown() = 0;
    virtual void Show() = 0;
    virtual void Update() = 0;

    bool Focused = false;

    Rectangle ContentRect = {0};
};
#endif

#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

class AnimationWindow : public DocumentWindow
{
public:
    SpriteAnimation *sprite;
    Texture2D texture;

    void Setup() override
    {
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

        texture = TextureManager::LoadTextureFromFile("game/assets/player/Heavy_Knight_Combat_Animations.png");
        texture.height *= 8;
        texture.width *= 8;

        sprite = new SpriteAnimation(texture, AnimatedSpriteInfo{4, 12, Vector2{0, 0}});

        sprite->addAnimationPositions(AnimationInfo{Vector2{0, 0}, 4, "current"});
        sprite->play("current");
    }

    void Shutdown() override
    {
        UnloadRenderTexture(ViewTexture);
    }

    void Show() override
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

        if (ImGui::Begin("Animation View", &Open, ImGuiWindowFlags_NoScrollbar))
        {
            Focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
            // draw the view
            rlImGuiImageRenderTextureFit(&ViewTexture, true);
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void Update() override
    {
        if (!Open)
            return;

        if (IsWindowResized())
        {
            UnloadRenderTexture(ViewTexture);
            ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        }

        sprite->move(Vector2{(float)(GetScreenWidth() / 2 - sprite->getWidth() / 2), (float)(50)});
        BeginTextureMode(ViewTexture);
        ClearBackground(SKYBLUE);

        DrawRectangle(sprite->getPosition().x, sprite->getPosition().y, sprite->getWidth(), sprite->getHeight(), RED);
        sprite->draw();

        // grid of cube trees on a plane to make a "world"
        EndTextureMode();
    }
};

#endif