#ifndef HIGGINS_H
#define HIGGINS_H

#include "Entity.h"
#include "IDrawable.h"

class Higgins : public Entity, public IDrawable
{
public:
	Higgins();
	~Higgins();

	virtual void Update(float timePassed);
	virtual void Draw(sf::RenderWindow& window);
private:

};

#endif