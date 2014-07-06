#include "Higgins.h"

Higgins::Higgins(EffectsManager& eManager) : Entity()
{
	effectsManager = &eManager;
	mPosition = sf::Vector2f(400,400);
	mVelocity = sf::Vector2f(0,0);
	mVelocityGoal = sf::Vector2f(0,0);

	baseQuad = sf::RectangleShape(sf::Vector2f(80,45));
	baseQuad.setOrigin(baseQuad.getSize().x/2,baseQuad.getSize().y/2);
	baseQuad.setFillColor(sf::Color(0,0,255,64));

	defensiveQuad = sf::RectangleShape(sf::Vector2f(60,170));
	defensiveQuad.setOrigin(defensiveQuad.getSize().x/2,defensiveQuad.getSize().y/2);
	defensiveQuad.setFillColor(sf::Color(0,255,0,64));

	if (!chargeTexture.loadFromFile("Art/Higgins/HigginsChargeLevels.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
    }
	SetUpChargeAnimations();
	BuildSpineCharacter();
	BuildCombos();

	mBaseStateMachine = std::make_shared<GamePlayStateMachine<Higgins> >(GamePlayStateMachine<Higgins>(this));
	mBaseStateMachine->SetCurrentState(HigginsIdle::Instance());

	mActionStateMachine = std::make_shared<GamePlayStateMachine<Higgins> >(GamePlayStateMachine<Higgins>(this));
	mActionStateMachine->SetCurrentState(HigginsWaiting::Instance());
}

Higgins::~Higgins()
{
	std::cout << "destroying";
	SkeletonData_dispose(skeletonData);
	Atlas_dispose(atlas);
	AnimationStateData_dispose(stateData);
	delete drawable;
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
	drawable->timeScale = 1.0f;

	skeleton = drawable->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;

	face = Face::Right;
	
	skeleton->x = 0;
	skeleton->y = 0;
	Skeleton_updateWorldTransform(skeleton);

	AnimationState_setAnimationByName(drawable->state, 0, "Idle", true);

	//add listener
	SetupCallBack();
}

void Higgins::SetUpChargeAnimations()
{
	//charge level one
	chargeOneAnimation.SetSpriteSheet(chargeTexture);
	chargeOneAnimation.AddFrame(sf::IntRect(766, 538, 248, 283));
	chargeOneAnimation.AddFrame(sf::IntRect(1502, 527, 236, 265));
	chargeOneAnimation.AddFrame(sf::IntRect(1256, 0, 242, 263));
	chargeOneAnimation.AddFrame(sf::IntRect(515, 0, 246, 259));
	chargeOneAnimation.AddFrame(sf::IntRect(1258, 265, 241, 258));
	chargeOneAnimation.AddFrame(sf::IntRect(1743, 0, 233, 252));
	chargeOneAnimation.AddFrame(sf::IntRect(0, 592, 256, 278));
	chargeOneAnimation.AddFrame(sf::IntRect(261, 0, 252, 268));

	//charge level two
	chargeTwoAnimation.SetSpriteSheet(chargeTexture);
	chargeTwoAnimation.AddFrame(sf::IntRect(260,298,252,288));
	chargeTwoAnimation.AddFrame(sf::IntRect(1740,527,236,274));
	chargeTwoAnimation.AddFrame(sf::IntRect(1013,265,243,261));
	chargeTwoAnimation.AddFrame(sf::IntRect(763,0,245,263));
	chargeTwoAnimation.AddFrame(sf::IntRect(1260,525,240,258));
	chargeTwoAnimation.AddFrame(sf::IntRect(1016,528,242,253));
	chargeTwoAnimation.AddFrame(sf::IntRect(1743,254,232,240));
	chargeTwoAnimation.AddFrame(sf::IntRect(0,298,258,292));

	//charge level three
	chargeThreeAnimation.SetSpriteSheet(chargeTexture);
	chargeThreeAnimation.AddFrame(sf::IntRect(258,592,254,297));
	chargeThreeAnimation.AddFrame(sf::IntRect(1502,253,239,272));
	chargeThreeAnimation.AddFrame(sf::IntRect(514,270,251,266));
	chargeThreeAnimation.AddFrame(sf::IntRect(514,538,250,267));
	chargeThreeAnimation.AddFrame(sf::IntRect(1010,0,244,263));
	chargeThreeAnimation.AddFrame(sf::IntRect(767,265,244,259));
	chargeThreeAnimation.AddFrame(sf::IntRect(1500,0,240,251));
	chargeThreeAnimation.AddFrame(sf::IntRect(0,0,259,296));

	currentChargeAnimation = &chargeOneAnimation;

	chargeSprite = AnimatedSprite(0.05f, false, true);
	chargeSprite.setPosition(sf::Vector2f(mPosition));
	chargeSprite.Play(*currentChargeAnimation);
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
	chargeSprite.setPosition(sf::Vector2f(mPosition.x - 110, mPosition.y - 225));
	defensiveQuad.setPosition(mPosition.x, mPosition.y - 85);
	baseQuad.setPosition(mPosition.x, mPosition.y - 20);
	skeleton->x = mPosition.x;
	skeleton->y = mPosition.y;

	window.draw(chargeSprite);
	window.draw(*drawable);
	window.draw(baseQuad);
	window.draw(defensiveQuad);
}

void Higgins::Update(const float timePassed)
{
	mVelocityGoal.x = 0;
	mVelocityGoal.y = 0;

	inputHandler.Update(timePassed);
	mBaseStateMachine->HandleInput(inputs);
	mActionStateMachine->HandleInput(inputs);
	
	mBaseStateMachine->Update(timePassed);
	mActionStateMachine->Update(timePassed);

	mVelocity.x = Approach(mVelocityGoal.x, mVelocity.x, timePassed * 1500);
	mVelocity.y = Approach(mVelocityGoal.y, mVelocity.y, timePassed * 1500);

	//update position and velocity
	mPosition = mPosition + mVelocity * timePassed;

	drawable->update(timePassed);
	chargeSprite.Update(timePassed);
}

void Higgins::SetAnimIdle()
{
	if(!mBaseStateMachine->isInState(HigginsIdle::Instance()))
	{
		mBaseStateMachine->ChangeState(HigginsIdle::Instance());
		AnimationState_setAnimationByName(drawable->state, 0, "Idle", true);
		Skeleton_setToSetupPose(drawable->skeleton);
	}
}

void Higgins::SetAnimRun()
{
	if(!mBaseStateMachine->isInState(HigginsMove::Instance()))
	{
		mBaseStateMachine->ChangeState(HigginsMove::Instance());
		AnimationState_setAnimationByName(drawable->state, 0, "Run", true);
		Skeleton_setToSetupPose(drawable->skeleton);
	}
}

void Higgins::StartAttack()
{
	mActionStateMachine->ChangeState(HigginsAttack::Instance());
	AnimationState_setAnimationByName(drawable->state, 1, "Attack", true);
	Skeleton_setToSetupPose(drawable->skeleton);
	currentChargeAnimation = &chargeOneAnimation;
	chargeSprite.Play(*currentChargeAnimation);
}

void Higgins::FireShot(float chargeLevel)
{
	//bool flip = false;
	//if(face == Face::Left) flip = true;
	sf::Vector2f shotPos(mPosition.x, mPosition.y - 115);
	if(face == Face::Right)
		shotPos.x += 40;
	else
		shotPos.x -= 80;
	effectsManager->AddEffect(0, shotPos, face);

	chargeSprite.Stop();
}

void Higgins::RemoveAttack()
{
	AnimationState_clearTrack(drawable->state, 1);
	mActionStateMachine->ChangeState(HigginsWaiting::Instance());
}

void Higgins::SetChargeLevelTwo()
{
	currentChargeAnimation = &chargeTwoAnimation;
	chargeSprite.Play(*currentChargeAnimation);
}

void Higgins::SetChargeLevelThree()
{
	currentChargeAnimation = &chargeThreeAnimation;
	chargeSprite.Play(*currentChargeAnimation);
}

void Higgins::FlipSkeleton(const bool value)
{
	if(value)
		face = Face::Left;
	else face = Face::Right;
	skeleton->flipX = value;
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
				//printf("%d start: %s\n", trackIndex, animationName);
				break;
			case ANIMATION_END:
				//printf("%d end: %s\n", trackIndex, animationName);
				value = std::strcmp(animationName, "Attack");
				if(value == 0)
				{
					//std::cout << "Reseting attack: ";
					//higgins->ClearAttack();
				}
				break;
			case ANIMATION_COMPLETE:
				//printf("%d complete: %s, %d\n", trackIndex, animationName, loopCount);
				break;
			case ANIMATION_EVENT:
				//printf("%d event: %s, %s: %d, %f, %s\n", trackIndex, animationName, event->data->name, event->intValue, event->floatValue,
						//event->stringValue);
				break;
		}
		fflush(stdout);
	};
}