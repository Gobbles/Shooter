#include "Higgins.h"

Higgins::Higgins() : Entity("")
{
	mPosition = sf::Vector2f(400,400);

	baseQuad = sf::RectangleShape(sf::Vector2f(100,35));
	baseQuad.setOrigin(baseQuad.getSize().x/2,baseQuad.getSize().y/2);
	baseQuad.setFillColor(sf::Color(0,0,255,64));

	defensiveQuad = sf::RectangleShape(sf::Vector2f(80,130));
	defensiveQuad.setOrigin(defensiveQuad.getSize().x/2,defensiveQuad.getSize().y/2);
	defensiveQuad.setFillColor(sf::Color(0,255,0,64));
}

Higgins::~Higgins()
{

}

void Higgins::Draw(sf::RenderWindow& window)
{
	//set quad positions
	defensiveQuad.setPosition(mPosition.x, mPosition.y - 55);
	baseQuad.setPosition(mPosition.x, mPosition.y);

	window.draw(baseQuad);
	window.draw(defensiveQuad);
}

void Higgins::Update(float timePassed)
{

}