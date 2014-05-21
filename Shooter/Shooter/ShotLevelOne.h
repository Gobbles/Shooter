#pragma once
#include "effect.h"
class ShotLevelOne : public Effect
{
public:
	//ctor and dtor
	ShotLevelOne() {}
	ShotLevelOne(const sf::Vector2f playerPosition, bool flip);
	~ShotLevelOne();

	//Interfaces
	virtual void Update(const float timePassed);
	virtual void Draw(sf::RenderWindow& window);

};

