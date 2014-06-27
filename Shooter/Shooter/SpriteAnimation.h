#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

class SpriteAnimation
{
public:
    SpriteAnimation();

    void AddFrame(sf::IntRect rect);
    void SetSpriteSheet(const sf::Texture& texture);

	//retrieve the spritesheet
    const sf::Texture* GetSpriteSheet() const;
	//retrieve the size of the frame list
    std::size_t GetSize() const;
	//retrieve a specific frame
    const sf::IntRect& GetFrame(std::size_t n) const;

private:
	//list of all the frames in the animation
    std::vector<sf::IntRect> mFrames;
	//texture to use for the animation
    const sf::Texture* mTexture;
};

#endif