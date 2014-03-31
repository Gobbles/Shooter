#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\Texture.hpp>

class Animation
{
public:
    Animation();

    void addFrame(sf::IntRect rect);
    void setSpriteSheet(const sf::Texture& texture);

	//retrieve the spritesheet
    const sf::Texture* getSpriteSheet() const;
	//retrieve the size of the frame list
    std::size_t getSize() const;
	//retrieve a specific frame
    const sf::IntRect& getFrame(std::size_t n) const;

private:
	//list of all the frames in the animation
    std::vector<sf::IntRect> mFrames;
	//texture to use for the animation
    const sf::Texture* mTexture;
};

#endif