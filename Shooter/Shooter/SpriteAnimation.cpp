#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation() : mTexture(NULL)
{

}

void SpriteAnimation::AddFrame(sf::IntRect rect)
{
    mFrames.push_back(rect);
}

void SpriteAnimation::SetSpriteSheet(const sf::Texture& texture)
{
    mTexture = &texture;
}

const sf::Texture* SpriteAnimation::GetSpriteSheet() const
{
    return mTexture;
}

std::size_t SpriteAnimation::GetSize() const
{
    return mFrames.size();
}

const sf::IntRect& SpriteAnimation::GetFrame(std::size_t n) const
{
    return mFrames[n];
}