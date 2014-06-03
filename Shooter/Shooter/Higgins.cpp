#include "Higgins.h"

Higgins::Higgins() : Entity()
{
	mPosition = sf::Vector2f(400,400);
	mVelocity = sf::Vector2f(0,0);

	baseQuad = sf::RectangleShape(sf::Vector2f(100,45));
	baseQuad.setOrigin(baseQuad.getSize().x/2,baseQuad.getSize().y/2);
	baseQuad.setFillColor(sf::Color(0,0,255,64));

	defensiveQuad = sf::RectangleShape(sf::Vector2f(80,180));
	defensiveQuad.setOrigin(defensiveQuad.getSize().x/2,defensiveQuad.getSize().y/2);
	defensiveQuad.setFillColor(sf::Color(0,255,0,64));

	BuildSpineCharacter();
	BuildCombos();

	mAnimStateMachine = std::make_shared<AnimationStateMachine<Higgins> >(AnimationStateMachine<Higgins>(this));
	mAnimStateMachine->SetCurrentState(HigginsIdle::Instance());
}

Higgins::~Higgins()
{
	std::cout << "destroying";
	SkeletonData_dispose(skeletonData);
	Atlas_dispose(atlas);
	AnimationStateData_dispose(stateData);
	delete drawable;
}

void Higgins::SetupAnimations()
{
	
}

void Higgins::BuildSpineCharacter()
{
	// Load atlas, skeleton, and animations.
	atlas = Atlas_createFromFile("Art/Higgins/Higgins.atlas", 0);
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = 1.0f;
	skeletonData = SkeletonJson_readSkeletonDataFile(json, "Art/Higgins/Higgins.json");

	SkeletonJson_dispose(json);

	// Configure mixing.
	stateData = AnimationStateData_create(skeletonData);
	
	/*//mix between walk and idle
	AnimationStateData_setMixByName(stateData, "Idle", "Walk", 0.2f);
	AnimationStateData_setMixByName(stateData, "Walk", "Idle", 0.2f);
	//mix between idle and run
	AnimationStateData_setMixByName(stateData, "Run", "Idle", 0.2f);
	AnimationStateData_setMixByName(stateData, "Idle", "Run", 0.2f);*/
	
	drawable = new spine::SkeletonDrawable(skeletonData, stateData);
	drawable->timeScale = 1;

	skeleton = drawable->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;
	
	skeleton->x = 0;
	skeleton->y = 0;
	Skeleton_updateWorldTransform(skeleton);

	AnimationState_setAnimationByName(drawable->state, 0, "Idle", true);

	//add listener
	SetupCallBack();
}

void Higgins::BuildCombos()
{
	Combos[0][0] = InputCommands::Input::Down;
	Combos[0][1] = InputCommands::Input::Right;
	Combos[0][2] = InputCommands::Input::Light_Attack;
	Combos[0][3] = InputCommands::Input::Invalid;
	Combos[0][4] = InputCommands::Input::Invalid;

	Combos[1][0] = InputCommands::Input::Down;
	Combos[1][1] = InputCommands::Input::Down;
	Combos[1][2] = InputCommands::Input::Down;
	Combos[1][3] = InputCommands::Input::Down;
	Combos[1][4] = InputCommands::Input::Down;

	Combos[2][0] = InputCommands::Input::Down;
	Combos[2][1] = InputCommands::Input::Down;
	Combos[2][2] = InputCommands::Input::Down;
	Combos[2][3] = InputCommands::Input::Down;
	Combos[2][4] = InputCommands::Input::Down;

	Combos[3][0] = InputCommands::Input::Down;
	Combos[3][1] = InputCommands::Input::Down;
	Combos[3][2] = InputCommands::Input::Right;
	Combos[3][3] = InputCommands::Input::Right;
	Combos[3][4] = InputCommands::Input::Light_Attack;
}

void Higgins::ProcessInput(sf::Event& event)
{
	if(CheckInput(event) == true)
	{
		int combo = CheckCombos();
		if(combo > -1)
		{
			std::cout << "Shoot Combo!: ";
			std::cout << combo;
			std::cout << "\n";
		}
	}
}

void Higgins::Draw(sf::RenderWindow& window)
{
	//set quad positions
	defensiveQuad.setPosition(mPosition.x, mPosition.y - 95);
	baseQuad.setPosition(mPosition.x, mPosition.y - 20);
	skeleton->x = mPosition.x;
	skeleton->y = mPosition.y;

	window.draw(*drawable);
	window.draw(baseQuad);
	window.draw(defensiveQuad);
}

void Higgins::Update(const float timePassed)
{
	if(moveDown)
		mVelocity.y = 300;
	else if(moveUp)
		mVelocity.y = -300;
	else
		mVelocity.y = 0;

	if(moveRight)
	{
		mVelocity.x = 300;
		skeleton->flipX = false;
	}
	else if(moveLeft)
	{
		mVelocity.x = -300;
		skeleton->flipX = true;
	}
	else
		mVelocity.x = 0;

	if(attack && !isAttacking)
	{
		isAttacking = true;
		//AnimationState_setAnimationByName(drawable->state, 1, "Attack", true);
	}
	else if(defend && !isBlocking && !isDodging)
	{
		std::cout << "Speed X: " << mVelocity.x;
		std::cout << " Speed Y: " << mVelocity.y;
		if(mVelocity.x != 0 || mVelocity.y != 0)
		{
			//dodgeroll
			std::cout << "DodgeRoll";
			if(moveLeft)
				mVelocity.x = -600;
			else if(moveRight)
				mVelocity.x = 600;
			//AnimationState_setAnimationByName(drawable->state, 0, "DodgeRoll", false);
		}
		else
		{
			std::cout << "Block";
			isBlocking = true;
			//block
		}
	}

	mPosition.x += mVelocity.x * timePassed;
	mPosition.y += mVelocity.y * timePassed;

	inputHandler.Update(timePassed);
	drawable->update(timePassed);
	mAnimStateMachine->Update();
}

void Higgins::SetAnimIdle()
{
	mAnimStateMachine->ChangeState(HigginsIdle::Instance());
	AnimationState_setAnimationByName(drawable->state, 0, "Idle", true);
	Skeleton_setToSetupPose(drawable->skeleton);
}

void Higgins::SetAnimRun()
{
	if(!mAnimStateMachine->isInState(HigginsMove::Instance()))
	{
		mAnimStateMachine->ChangeState(HigginsMove::Instance());
		AnimationState_setAnimationByName(drawable->state, 0, "Run", true);
		Skeleton_setToSetupPose(drawable->skeleton);
	}
}

void Higgins::SetupCallBack()
{
	//we keep a reference of this class inside the AnimationState, so we can use it later
	drawable->state->rendererObject = this;

	drawable->state->listener = [](AnimationState* state, int trackIndex, EventType type, Event* event, int loopCount)
	{
		Higgins* higgins = (Higgins*) state->rendererObject;
		TrackEntry* entry = AnimationState_getCurrent(state, trackIndex);
		const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;
		int value;
		switch (type) 
		{
			case ANIMATION_START:
				printf("%d start: %s\n", trackIndex, animationName);
				break;
			case ANIMATION_END:
				printf("%d end: %s\n", trackIndex, animationName);
				value = std::strcmp(animationName, "Attack");
				if(value != -1)
				{
					std::cout << "Reseting attack: ";
					higgins->isAttacking = false;
					higgins->attack = false;
					std::cout << higgins->isAttacking;
				}
				break;
			case ANIMATION_COMPLETE:
				printf("%d complete: %s, %d\n", trackIndex, animationName, loopCount);
				break;
			case ANIMATION_EVENT:
				printf("%d event: %s, %s: %d, %f, %s\n", trackIndex, animationName, event->data->name, event->intValue, event->floatValue,
						event->stringValue);
				break;
		}
		fflush(stdout);
	};
}