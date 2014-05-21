#ifndef HIGGINS_H
#define HIGGINS_H

#include "Entity.h"

#include "AnimationStateMachine.h"
#include "HigginsOwnedStates.h"
#include <functional>

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

	std::string name;
private:

	void BuildCombos();
	void BuildSpineCharacter();

	//animation State Machine
	std::shared_ptr<AnimationStateMachine<Higgins> > mAnimStateMachine;
	void AnimationResponse(AnimationState* state, int trackIndex, EventType type, Event* event, int loopCount);
};

#endif