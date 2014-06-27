#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <spine\spine-sfml.h>
#include "InputHandler.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "EffectsManager.h"

enum Face
{
	Right = 0,
	Left
};

class Entity : public IDrawable, public IUpdateable
{
protected:
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
	
	//facing
	Face face;

public:
	sf::RectangleShape baseQuad;
	sf::RectangleShape defensiveQuad;
	sf::RectangleShape offensiveQuad;
	//members
	sf::Vector2f mVelocity;
	sf::Vector2f mPosition;

	//virtual void Move() {};
	bool CheckInput(sf::Event &event);
	
	Entity();
	virtual ~Entity();

	std::vector<bool> inputs;
};

#endif