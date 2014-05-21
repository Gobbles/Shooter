#ifndef EFFECT_H
#define EFFECT_H

#include "IDrawable.h"
#include "IUpdateable.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"

class Effect :	public IDrawable, public IUpdateable
{
public:
	Effect(){}
	virtual ~Effect(){}

	//Interfaces
	virtual void Update(const float timePassed) {}
	virtual void Draw(sf::RenderWindow& window) {}
	/**************************************
	*	MEMBERS
	***************************************/
	//position and veloctiy
	sf::Vector2f mVelocity;
	sf::Vector2f mPosition;
	//texture and sprite(will later be an animation
protected:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	//a base quad and an offensive quad for effects, no defensive quad needed
	sf::RectangleShape mBaseQuad;
	sf::RectangleShape mOffensiveQuad;
};

#endif // EFFECT_H