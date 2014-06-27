#ifndef EFFECTS_MANAGER_H
#define EFFECTS_MANAGER_H

#include <vector>
#include <memory>
#include "Effect.h"
#include "ShotLevelOne.h"

class Entity;
class EffectsManager
{
private:
	//list of effects
	std::vector<std::shared_ptr<Effect> > effectList;

public:
	EffectsManager();
	void Update(float timePassed);
	void Draw(sf::RenderWindow& window);
	void CheckCollisions(Entity& entity);
	void AddEffect(int id, sf::Vector2f position, bool flip);
	void RemoveEffect(Effect* effect);
};

#endif