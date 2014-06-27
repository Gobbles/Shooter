#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(float frameTime, bool paused, bool looped) :
    mAnimation(NULL), mFrameTime(frameTime), mCurrentFrame(0), mIsPaused(paused), mIsLooped(looped), mTexture(NULL)
{

}

void AnimatedSprite::SetAnimation(const SpriteAnimation& animation)
{
    mAnimation = &animation;
    mTexture = mAnimation->GetSpriteSheet();
    mCurrentFrame = 0;
    SetFrame(mCurrentFrame);
}

void AnimatedSprite::SetFrameTime(float time)
{
    mFrameTime = time;
}

void AnimatedSprite::Play()
{
    mIsPaused = false;
}

void AnimatedSprite::Play(const SpriteAnimation& animation)
{
    if (GetAnimation() != &animation)
        SetAnimation(animation);
    Play();
}

void AnimatedSprite::Pause()
{
    mIsPaused = true;
}

void AnimatedSprite::Stop()
{
    mIsPaused = true;
    mCurrentFrame = 0;
    SetFrame(mCurrentFrame);
}

void AnimatedSprite::SetLooped(bool looped)
{
    mIsLooped = looped;
}

void AnimatedSprite::SetColor(const sf::Color& color)
{
    // Update the vertices' color
    mVertices[0].color = color;
    mVertices[1].color = color;
    mVertices[2].color = color;
    mVertices[3].color = color;
}

const SpriteAnimation* AnimatedSprite::GetAnimation() const
{
    return mAnimation;
}

sf::FloatRect AnimatedSprite::GetLocalBounds() const
{
    sf::IntRect rect = mAnimation->GetFrame(mCurrentFrame);

    float width = static_cast<float>(std::abs(rect.width));
    float height = static_cast<float>(std::abs(rect.height));

    return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect AnimatedSprite::GetGlobalBounds() const
{
    return getTransform().transformRect(GetLocalBounds());
}

bool AnimatedSprite::IsLooped() const
{
    return mIsLooped;
}

bool AnimatedSprite::IsPlaying() const
{
    return !mIsPaused;
}

float AnimatedSprite::GetFrameTime() const
{
    return mFrameTime;
}

void AnimatedSprite::SetFrame(std::size_t newFrame, bool resetTime)
{
    if (mAnimation)
    {
        //calculate new vertex positions and texture coordiantes
        sf::IntRect rect = mAnimation->GetFrame(newFrame);

        mVertices[0].position = sf::Vector2f(0.f, 0.f);
        mVertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
        mVertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
        mVertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

        float left = static_cast<float>(rect.left) + 0.0001f;
        float right = left + static_cast<float>(rect.width);
        float top = static_cast<float>(rect.top);
        float bottom = top + static_cast<float>(rect.height);

        mVertices[0].texCoords = sf::Vector2f(left, top);
        mVertices[1].texCoords = sf::Vector2f(left, bottom);
        mVertices[2].texCoords = sf::Vector2f(right, bottom);
        mVertices[3].texCoords = sf::Vector2f(right, top);
    }

    if (resetTime)
        mCurrentTime = 0.0f;
}

void AnimatedSprite::Update(float timePassed)
{
    // if not paused and we have a valid animation
    if (!mIsPaused && mAnimation)
    {
        // add delta time
        mCurrentTime += timePassed;

        // if current time is bigger then the frame time advance one frame
        if (mCurrentTime >= mFrameTime)
        {
            // reset time, but keep the remainder
			mCurrentTime -= mFrameTime;

            // get next Frame index
            if (mCurrentFrame + 1 < mAnimation->GetSize())
                mCurrentFrame++;
            else
            {
                // animation has ended
                mCurrentFrame = 0; // reset to start

                if (!mIsLooped)
                {
                    mIsPaused = true;
                }

            }

            // set the current frame, not reseting the time
            SetFrame(mCurrentFrame, false);
        }
    }
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mAnimation && mTexture)
    {
        states.transform *= getTransform();
        states.texture = mTexture;
        target.draw(mVertices, 4, sf::Quads, states);
    }
}