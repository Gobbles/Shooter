#ifndef HIGGINS_H
#define HIGGINS_H

#include "Entity.h"
#include "IDrawable.h"
#include "AnimationStateMachine.h"
#include "HigginsOwnedStates.h"

class Higgins : public Entity, public IDrawable
{
public:
	Higgins();
	~Higgins();

	virtual void Update(float timePassed);
	virtual void Draw(sf::RenderWindow& window);

	void SetupAnimations();
	void ProcessInput(sf::Event& event);

	void SetAnimIdle();
	void SetAnimRun();

	//texture and sprite
	sf::Texture playerTexture;
private:

	void BuildCombos();

	//animation State Machine
	std::shared_ptr<AnimationStateMachine<Higgins> > mAnimStateMachine;
};

#endif