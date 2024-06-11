#include "SpriteAnimation.h"
#include <format>

SpriteAnimation::SpriteAnimation(Texture2D texture, AnimatedSpriteInfo spriteInfo)
{
    if (spriteInfo.animCols == 0)
    {
        spriteInfo.animCols = 1;
    }
    if (spriteInfo.animRows == 0)
    {
        spriteInfo.animRows = 1;
    }

    m_texture = texture;

    m_animCols = spriteInfo.animCols;
    m_animRows = spriteInfo.animRows;

    m_widthOffset = m_texture.width / spriteInfo.animCols;
    m_heightOffset = m_texture.height / spriteInfo.animRows;

    m_animWidth = m_texture.width / m_animCols;
    m_animHeight = m_texture.height / m_animRows;

    m_frameRec = getRectangle(Vector2{0, 0});

    m_position = spriteInfo.pos;
}

void SpriteAnimation::draw()
{
    setCurrentFrame();
    DrawTextureRec(m_texture, m_frameRec, m_position, WHITE);
}

void SpriteAnimation::play(std::string name)
{
    if (m_currentAnimation.name == name)
        return;
    // if (m_isAnimationPlaying)
    //     return;
    if (!hasAnimation(name))
    {
        // TODO:WARNING HERE
        std::cout << "Animation: Animation not found." << "\n";
        return;
    }
    if (name != "idle")
    {
        // std::cout << "Animation Playing " << name << "\n";
    }

    AnimationInfo info = m_animationPosition[name];
    /** Create Path from info */
    /************** */
    m_maxFrame = info.maxFrames;
    m_currentAnimation = info;
    createAnimationArray();
}
void SpriteAnimation::createAnimationArray()
{
    m_shouldReset = true;

    int currentCol = m_currentAnimation.position.x;
    int currentRow = m_currentAnimation.position.y;
    std::vector<Rectangle> rectArr;
    for (int i = 0; i < m_maxFrame; ++i)
    {
        float xStart = currentCol * m_widthOffset;
        float yStart = currentRow * m_heightOffset;

        // std::cout << std::format("Pushing in x: {} y: {}\n", xStart, yStart);
        currentCol++;
        Rectangle rect = Rectangle{xStart, yStart};
        rectArr.push_back(rect);
        // We are going over the width
        // Not working about yStart b/c We are going from left to right
        if (xStart >= m_texture.width)
        {
            // Go to the next line
            currentRow++;
            // Reset the x
            currentCol = 0;
        }
    }
    m_animationPath = rectArr;
}

void SpriteAnimation::move(Vector2 newPosition)
{
    m_position = newPosition;
}

void SpriteAnimation::addAnimationPositions(AnimationInfo info)
{
    m_animationPosition[info.name] = info;
}

// BUG: When we switch to a different animation we play the current animaiton for a bit b/c of the time inbetween frame ticks
void SpriteAnimation::setCurrentFrame()
{
    if (m_animationPath.empty())
        return;
    // m_isAnimationPlaying = false;
    m_frameCounter++; // increment past 0 for the first frame

    // Time for next frame
    if (m_frameCounter >= (60 / m_frameSpeed))
    {
        // std::cout << std::format("Current animation \n\tname: {}\n", m_currentAnimation.name);
        if (m_shouldReset)
        {
            m_shouldReset = false;
            m_isAnimationPlaying = false;
            m_frameCounter = 0;
            m_currentFrame = 0;
            m_currentRow = 0;
        }
        // TODO: Need signaling
        m_isAnimationPlaying = true;
        m_frameCounter = 0;

        // std::cout << std::format("Current animation path {}) x: {} y: {}\n", m_currentFrame, m_animationPath[m_currentFrame].x, m_animationPath[m_currentFrame].y);

        m_frameRec.x = m_animationPath[m_currentFrame].x;
        m_frameRec.y = m_animationPath[m_currentFrame].y;

        m_currentFrame++;

        if (m_currentFrame >= m_maxFrame)
        {
            // Signal
            m_isAnimationPlaying = false;
            m_currentFrame = 0;
            m_currentRow = 0;
        }
    }
}

Rectangle SpriteAnimation::getRectangle(Vector2 pos)
{
    return Rectangle{pos.x * m_widthOffset, pos.y * m_heightOffset, (float)m_animWidth, (float)m_animHeight};
}
