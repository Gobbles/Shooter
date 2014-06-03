#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <spine\spine-sfml.h>
#include "InputHandler.h"
#include "IDrawable.h"
#include "IUpdateable.h"

class Entity : public IDrawable, public IUpdateable
{
protected:
	//members
	sf::Vector2f mVelocity;
	
	sf::RectangleShape baseQuad;
	sf::RectangleShape defensiveQuad;
	sf::RectangleShape offensiveQuad;

	InputHandler inputHandler;

	InputCommands::Input Combos[4][5];

	int CheckCombos();

	//Interfaces
	virtual void Update(const float timePassed) {}
	virtual void Draw(sf::RenderWindow& window) {}

	//Spine information
	Atlas* atlas;
	SkeletonData *skeletonData;

	spine::SkeletonDrawable* drawable;
	Skeleton* skeleton;

	//State data
	AnimationStateData* stateData;

public:
	sf::Vector2f mPosition;

	virtual void Move() {};
	bool CheckInput(sf::Event &event);
	
	Entity();
	virtual ~Entity();

	//movement booleans
	bool moveUp;
	bool moveLeft;
	bool moveRight;
	bool moveDown;

	//attack
	bool attack;
	bool isAttacking;

	//defence
	bool defend;

	//control States
	bool isDodging;
	bool isBlocking;
};

#endif