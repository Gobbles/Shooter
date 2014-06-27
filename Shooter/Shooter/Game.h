#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Higgins.h"
#include "ShotLevelOne.h"
#include "EffectsManager.h"

class Game
{
public:
	Game();
	~Game();

	void Run();
private:
	void ProcessEvents();
	void CheckEvents(sf::Event &event);
	void Update(float timePassed);
	void CheckCollisions();
	void Draw();

	sf::RenderWindow window;
	sf::Texture mapTexture;
	sf::Sprite mapSprite;

	//Higgins Player1;
	std::vector<std::shared_ptr<Entity> > mGameEntities;
	std::shared_ptr<Higgins> Player1;

	//EffectManager
	std::unique_ptr<EffectsManager> mEffectsManager;
};

#endif