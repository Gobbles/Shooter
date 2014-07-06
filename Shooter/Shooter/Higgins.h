#ifndef HIGGINS_H
#define HIGGINS_H

#include <functional>
#include "Entity.h"
#include "AnimatedSprite.h"
#include "GamePlayStateMachine.h"
#include "HigginsActionStates.h"
#include "HigginsBaseStates.h"
//#include "Maths.h"


class Higgins : public Entity
{
public:
	Higgins(EffectsManager& eManager);
	~Higgins();

	virtual void Update(const float timePassed);
	virtual void Draw(sf::RenderWindow& window);

	void ProcessInput(sf::Event& event);

	void SetAnimIdle();
	void SetAnimRun();

	void StartAttack();
	void FireShot(float chargeLevel);
	void RemoveAttack();
	void SetChargeLevelTwo();
	void SetChargeLevelThree();

	void FlipSkeleton(const bool value);
private:

	void BuildCombos();
	void BuildSpineCharacter();

	EffectsManager* effectsManager;

	//animation State Machine
	std::shared_ptr<GamePlayStateMachine<Higgins> > mBaseStateMachine;
	std::shared_ptr<GamePlayStateMachine<Higgins> > mActionStateMachine;
	void SetupCallBack();

	//charging animations
	SpriteAnimation chargeOneAnimation;
	SpriteAnimation chargeTwoAnimation;
	SpriteAnimation chargeThreeAnimation;

	SpriteAnimation* currentChargeAnimation;
	AnimatedSprite chargeSprite;

	void SetUpChargeAnimations();

	sf::Texture chargeTexture;
};

#endif