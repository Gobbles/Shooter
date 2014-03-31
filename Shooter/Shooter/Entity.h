#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include "InputHandler.h"


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

	InputHandler inputHandler;

	InputCommands::Input Combos[4][5];

	int CheckCombos();

public:
	virtual void Move() {};
	bool CheckInput(sf::Event &event);
	
	Entity(std::string fileLocation);
	virtual ~Entity() {}

	//movement booleans
	bool moveUp;
	bool moveLeft;
	bool moveRight;
	bool moveDown;
};

#endif