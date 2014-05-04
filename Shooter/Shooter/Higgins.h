#ifndef HIGGINS_H
#define HIGGINS_H

#include "Entity.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "AnimationStateMachine.h"
#include "HigginsOwnedStates.h"

class Higgins : public Entity, public IDrawable, public IUpdateable
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
private:

	void BuildCombos();
	void BuildSpineCharacter();

	//animation State Machine
	std::shared_ptr<AnimationStateMachine<Higgins> > mAnimStateMachine;
};

#endif