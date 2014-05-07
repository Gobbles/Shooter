#ifndef HIGGINS_H
#define HIGGINS_H

#include "Entity.h"

#include "AnimationStateMachine.h"
#include "HigginsOwnedStates.h"

class Higgins : public Entity
{
public:
	Higgins();
	~Higgins();

	virtual void Update(const float timePassed);
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