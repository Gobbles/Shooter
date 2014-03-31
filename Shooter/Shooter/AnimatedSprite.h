#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "Animation.h"

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
    explicit AnimatedSprite(float frameTime = 0.2f, bool paused = false, bool looped = true);

    void Update(float timePassed);
    void setAnimation(const Animation& animation);
    void setFrameTime(float time);
    void play();
    void play(const Animation& animation);
    void pause();
    void stop();
    void setLooped(bool looped);
    void setColor(const sf::Color& color);
    const Animation* getAnimation() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
    bool isLooped() const;
    bool isPlaying() const;
    float getFrameTime() const;
    void setFrame(std::size_t newFrame, bool resetTime = true);

private:
    const Animation* mAnimation;
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