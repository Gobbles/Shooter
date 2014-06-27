#ifndef SHOT_ONE_H
#define SHOT_ONE_H

#include "effect.h"
class EffectsManager;
class ShotLevelOne : public Effect
{
public:
	//ctor and dtor
	ShotLevelOne() {}
	ShotLevelOne(EffectsManager* eManager, const sf::Vector2f playerPosition, bool flip);
	~ShotLevelOne();

	//Interfaces
	virtual void Update(const float timePassed);
	virtual void Draw(sf::RenderWindow& window);

	float travelDistance;

private:
	EffectsManager* effectsManager;

	virtual void Kill();
};

#endif
