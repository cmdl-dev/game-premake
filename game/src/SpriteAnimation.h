
#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "raylib.h"
#include "TextureManager.h"
#include <string>
#include <map>
#include <iostream>
#include <vector>

struct AnimationInfo
{                     // Structure declaration
    Vector2 position; // Member (int variable)
    int maxFrames;    // Member (string variable)
    std::string name;
};

struct AnimatedSpriteInfo
{
    int animCols;
    int animRows;
    Vector2 pos;
};
// TODO: make animation not load sprite every time
class SpriteAnimation
{
public:
    SpriteAnimation(Texture2D texture, AnimatedSpriteInfo spriteInfo);

    void draw();
    void play(std::string name);
    void move(Vector2 newPosition);
    void resize(float scale);

    void addAnimationPositions(AnimationInfo info);
    void setFrameSpeed(int speed) { m_frameSpeed = speed; };
    int getFrameSpeed() { return m_frameSpeed; };

    Texture2D m_texture;
    float m_scale = 1.0f;

private:
    bool hasAnimation(std::string name) { return m_animationPosition.find(name) != m_animationPosition.end(); };

    void setCurrentFrame();
    void createAnimationArray();

    Rectangle getRectangle(Vector2 pos);
    std::map<std::string, AnimationInfo> m_animationPosition;

    Vector2 m_position;
    Rectangle m_frameRec;
    AnimationInfo m_currentAnimation;

    std::vector<Rectangle> m_animationPath;

    bool m_shouldReset = false;
    bool m_isAnimationPlaying = false;

    int m_animCols;
    int m_animRows;

    int m_widthOffset;
    int m_heightOffset;

    int m_animWidth;
    int m_animHeight;

    int m_frameCounter = 0; // Handle framerate
    int m_currentFrame = 0;
    int m_frameSpeed = 2;
    int m_maxFrame; // it includes
    int m_currentRow = 0;
};
#endif
