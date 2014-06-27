#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "SpriteAnimation.h"

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
    explicit AnimatedSprite(float frameTime = 0.2f, bool paused = false, bool looped = true);

    void Update(float timePassed);
    void SetAnimation(const SpriteAnimation& animation);
    void SetFrameTime(float time);
    void Play();
    void Play(const SpriteAnimation& animation);
    void Pause();
    void Stop();
    void SetLooped(bool looped);
    void SetColor(const sf::Color& color);
    const SpriteAnimation* GetAnimation() const;
    sf::FloatRect GetLocalBounds() const;
    sf::FloatRect GetGlobalBounds() const;
    bool IsLooped() const;
    bool IsPlaying() const;
    float GetFrameTime() const;
    void SetFrame(std::size_t newFrame, bool resetTime = true);

private:
    const SpriteAnimation* mAnimation;
    float mFrameTime;
    float mCurrentTime;
    std::size_t mCurrentFrame;
    bool mIsPaused;
    bool mIsLooped;
    const sf::Texture* mTexture;
    sf::Vertex mVertices[4];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif