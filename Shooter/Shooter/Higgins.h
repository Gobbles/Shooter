#ifndef HIGGINS_H
#define HIGGINS_H

#include "Entity.h"

#include "GamePlayStateMachine.h"
#include "HigginsActionStates.h"
#include "HigginsBaseStates.h"
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

	void StartAttack();
	void FireShot(float chargeLevel);
	void RemoveAttack();

	void FlipSkeleton(const bool value);
private:

	void BuildCombos();
	void BuildSpineCharacter();

	//animation State Machine
	std::shared_ptr<GamePlayStateMachine<Higgins> > mBaseStateMachine;
	std::shared_ptr<GamePlayStateMachine<Higgins> > mActionStateMachine;
	void SetupCallBack();
};

#endif