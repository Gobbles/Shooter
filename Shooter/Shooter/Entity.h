#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>

class Entity
{
protected:
	//members
	sf::Texture mTexture;
	sf::Sprite mSprite;

	sf::Vector2f mVelocity;
	sf::Vector2f mPosition;

	sf::RectangleShape baseQuad;
	sf::RectangleShape defensiveQuad;
	sf::RectangleShape offensiveQuad;
public:
	virtual void Move() {};
	
	Entity(std::string fileLocation) {}
	virtual ~Entity() {}
};

#endif