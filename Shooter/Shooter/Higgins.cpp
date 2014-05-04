#include "Higgins.h"

Higgins::Higgins() : Entity()
{
	mPosition = sf::Vector2f(400,400);

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
	atlas = Atlas_readAtlasFile("Art/Higgins/Higgins.atlas");
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = 0.22;
	skeletonData = SkeletonJson_readSkeletonDataFile(json, "Art/Higgins/Higgins.json");
	walkAnimation = SkeletonData_findAnimation(skeletonData, "Walk");
	runAnimation = SkeletonData_findAnimation(skeletonData, "Run");
	idleAnimation = SkeletonData_findAnimation(skeletonData, "Idle");
	SkeletonJson_dispose(json);

	// Configure mixing.
	stateData = AnimationStateData_create(skeletonData);
	//mix between walk and idle
	AnimationStateData_setMixByName(stateData, "Idle", "Walk", 0.2f);
	AnimationStateData_setMixByName(stateData, "Walk", "Idle", 0.2f);
	//mix between idle and run
	AnimationStateData_setMixByName(stateData, "Run", "Idle", 0.2f);
	AnimationStateData_setMixByName(stateData, "Idle", "Run", 0.2f);

	drawable = new spine::SkeletonDrawable(skeletonData, stateData);
	drawable->timeScale = 0.5;

	skeleton = drawable->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;
	//Skeleton_setSkinByName(skeleton, "HigginsMain");
	//Skeleton_setSlotsToSetupPose(skeleton);
//	Skeleton_setAttachment(skeleton, "left hand item", "dagger");

	skeleton->x = 0;
	skeleton->y = 0;
	Skeleton_updateWorldTransform(skeleton);

	AnimationState_setAnimationByName(drawable->state, 0, "Idle", true);
	//AnimationState_addAnimationByName(drawable->state, 0, "walk", false, 0);
	//AnimationState_addAnimationByName(drawable->state, 0, "run", false, 0);
	//AnimationState_addAnimationByName(drawable->state, 0, "idle", true, 0);
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

void Higgins::Update(float timePassed)
{
	inputHandler.Update(timePassed);
	drawable->update(timePassed);
	mAnimStateMachine->Update();
}

void Higgins::SetAnimIdle()
{
	mAnimStateMachine->ChangeState(HigginsIdle::Instance());
	AnimationState_setAnimationByName(drawable->state, 0, "Idle", true);
}

void Higgins::SetAnimRun()
{
	mAnimStateMachine->ChangeState(HigginsMove::Instance());
	AnimationState_setAnimationByName(drawable->state, 0, "Run", true);
}