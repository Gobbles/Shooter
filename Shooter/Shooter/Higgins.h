#ifndef HIGGINS_H
#define HIGGINS_H

#include "Entity.h"
#include "IDrawable.h"
#include "AnimatedSprite.h"
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
	AnimatedSprite animationSprite;

	//currently playing Animation
	Animation* currentAnimation;

	//animations
	Animation idleAnimation;
	Animation runAnimation;

private:

	void BuildCombos();

	//animation State Machine
	std::shared_ptr<AnimationStateMachine<Higgins> > mAnimStateMachine;
};

#endif