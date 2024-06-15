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

    virtual void Setup(Texture2D texture, AnimatedSpriteInfo info, AnimationInfo animInfo, float scale) = 0;
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
    AnimationWindow(){};
    SpriteAnimation *sprite;
    Texture2D texture;

    void Close()
    {
        Open = false;
    }

    void ResetNewTexture(Texture2D texture, AnimatedSpriteInfo info, float scale)
    {

        texture.height *= scale;
        texture.width *= scale;
        sprite = new SpriteAnimation(texture, info);
    };

    void SetAnimationPosition(AnimationInfo animInfo)
    {
        sprite->addAnimationPositions(animInfo);
        sprite->play(animInfo.name);
    }

    void Setup(Texture2D texture, AnimatedSpriteInfo info, AnimationInfo animInfo, float scale) override
    {
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

        ResetNewTexture(texture, info, scale);
        SetAnimationPosition(animInfo);
        Open = true;
    }

    void Shutdown() override
    {
        Close();
        UnloadRenderTexture(ViewTexture);
    }

    void Show() override
    {
        if (!Open)
            return;
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