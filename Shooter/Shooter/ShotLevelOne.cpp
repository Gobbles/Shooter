#include "ShotLevelOne.h"
#include <iostream>

ShotLevelOne::ShotLevelOne(const sf::Vector2f shotPosition, bool flip)
{
	//texture and sprite(will later be an animation
	if(!mTexture.loadFromFile("Art/shot.png"))
	{
		std::cout << "Error";
	}
	mSprite.setTexture(mTexture);

	//position and veloctiy
	mVelocity = sf::Vector2f(1000,0);
	mPosition = shotPosition;

	if(flip)
	{
		// flip X
		mSprite.setTextureRect(sf::IntRect(41, 0, -41, 21));
		mVelocity = sf::Vector2f(-400,0);
	}

	//a base quad and an offensive quad for effects, no defensive quad needed
	mBaseQuad = sf::RectangleShape(sf::Vector2f(41,45));
	mBaseQuad.setOrigin(mBaseQuad.getSize().x/2,mBaseQuad.getSize().y/2);
	mBaseQuad.setFillColor(sf::Color(0,0,255,64));
	
	mOffensiveQuad = sf::RectangleShape(sf::Vector2f(41,21));
	mOffensiveQuad.setOrigin(mOffensiveQuad.getSize().x/2,mOffensiveQuad.getSize().y/2);
	mOffensiveQuad.setFillColor(sf::Color(255,0,0,64));

	mSprite.setPosition(mPosition);
	mBaseQuad.setPosition(sf::Vector2f(mPosition.x + 21, mPosition.y + 80));
	mOffensiveQuad.setPosition(sf::Vector2f(mPosition.x + 21, mPosition.y + 10));
}

ShotLevelOne::~ShotLevelOne()
{
}

void ShotLevelOne::Update(const float timePassed)
{
	mPosition.x += mVelocity.x * timePassed;
	if(mPosition.x > 1280) mPosition.x = 0;
	mPosition.y += mVelocity.y * timePassed;

	mSprite.setPosition(mPosition);
	mBaseQuad.setPosition(sf::Vector2f(mPosition.x + 21, mPosition.y + 80));
	mOffensiveQuad.setPosition(sf::Vector2f(mPosition.x + 21, mPosition.y + 10));
}

void ShotLevelOne::Draw(sf::RenderWindow& window)
{
	window.draw(mSprite);
	window.draw(mBaseQuad);
	window.draw(mOffensiveQuad);
}
