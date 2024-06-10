#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(Texture2D texture, AnimatedSpriteInfo spriteInfo)
{
    m_texture = texture;

    m_animCols = spriteInfo.animCols;
    m_animRows = spriteInfo.animRows;

    m_widthOffset = m_texture.width / spriteInfo.animCols;
    m_heightOffset = m_texture.height / spriteInfo.animRows;

    m_animWidth = m_texture.width / m_animCols;
    m_animHeight = m_texture.height / m_animRows;

    m_frameRec = getRectangle(Vector2{0, 0});

    m_position = spriteInfo.pos;

    // addAnimationPositions("attackRight", AnimationInfo{Vector2{0, 0}, 4});
    // addAnimationPositions("attackRight2", AnimationInfo{Vector2{0, 0}, 7});
}

void SpriteAnimation::draw()
{
    setCurrentFrame();
    DrawTextureRec(m_texture, m_frameRec, m_position, WHITE);
}

void SpriteAnimation::play(std::string name)
{
    if (m_isAnimationPlaying)
        return;
    if (!hasAnimation(name))
    {
        // TODO:WARNING HERE
        std::cout << "Animation: Animation not found." << "\n";
        return;
    }

    AnimationInfo info = m_animationPosition[name];
    m_maxFrame = info.maxFrames;
    m_frameRec = getRectangle(info.position);

    m_currentAnimation = info;
}

void SpriteAnimation::move(Vector2 newPosition)
{
    m_position = newPosition;
}

void SpriteAnimation::addAnimationPositions(std::string name, AnimationInfo info)
{
    m_animationPosition[name] = info;
}

void SpriteAnimation::setCurrentFrame()
{

    // m_isAnimationPlaying = false;
    m_frameCounter++; // increment past 0 for the first frame

    // Time for next frame
    if (m_frameCounter >= (60 / m_frameSpeed))
    {
        m_isAnimationPlaying = true;
        m_frameCounter = 0;
        m_currentFrame++;

        if (m_currentFrame % m_animCols == 0 && m_currentFrame != 0)
            m_currentRow++;

        if (m_currentFrame >= m_maxFrame)
        {
            m_isAnimationPlaying = false;
            m_currentFrame = 0;
            m_currentRow = 0;
            resetAnimation();
        }

        // NOTE: Only supports animations that go from left to right not up and down
        m_frameRec.x = (float)m_currentFrame * m_texture.width / m_animCols;

        if (m_currentRow > 0)
            m_frameRec.y = (float)m_currentRow * m_texture.height / m_animRows;
    }
}

Rectangle SpriteAnimation::getRectangle(Vector2 pos)
{
    return Rectangle{pos.x * m_widthOffset, pos.y * m_heightOffset, (float)m_animWidth, (float)m_animHeight};
}