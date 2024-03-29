#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include <SFML\Graphics\RenderWindow.hpp>

class IDrawable
{
public:
	virtual ~IDrawable(){}
	virtual void Draw(sf::RenderWindow& window) = 0;
};

#endif