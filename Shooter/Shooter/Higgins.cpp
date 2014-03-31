#include "Higgins.h"

Higgins::Higgins() : Entity("")
{
	mPosition = sf::Vector2f(400,400);

	baseQuad = sf::RectangleShape(sf::Vector2f(100,35));
	baseQuad.setOrigin(baseQuad.getSize().x/2,baseQuad.getSize().y/2);
	baseQuad.setFillColor(sf::Color(0,0,255,64));

	defensiveQuad = sf::RectangleShape(sf::Vector2f(80,220));
	defensiveQuad.setOrigin(defensiveQuad.getSize().x/2,defensiveQuad.getSize().y/2);
	defensiveQuad.setFillColor(sf::Color(0,255,0,64));

	if (!playerTexture.loadFromFile("Art/Higgins.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
    }
	BuildCombos();
}

Higgins::~Higgins()
{
	//delete mAnimStateMachine;
}

void Higgins::SetupAnimations()
{
    idleAnimation.setSpriteSheet(playerTexture);
    idleAnimation.addFrame(sf::IntRect(0, 0, 256, 256));
    idleAnimation.addFrame(sf::IntRect(256, 0, 256, 256));
    idleAnimation.addFrame(sf::IntRect(0, 256, 256, 256));
    idleAnimation.addFrame(sf::IntRect(256, 256, 256, 256));

	runAnimation.setSpriteSheet(playerTexture);
	runAnimation.addFrame(sf::IntRect(512, 0, 256, 256));
	runAnimation.addFrame(sf::IntRect(512, 256, 256, 256));
	runAnimation.addFrame(sf::IntRect(768, 0, 256, 256));
	runAnimation.addFrame(sf::IntRect(768, 256, 256, 256));
	runAnimation.addFrame(sf::IntRect(0, 512, 256, 256));
	runAnimation.addFrame(sf::IntRect(0, 768, 256, 256));
	runAnimation.addFrame(sf::IntRect(256, 512, 256, 256));
	runAnimation.addFrame(sf::IntRect(512, 512, 256, 256));

	currentAnimation = &idleAnimation;

	// set up AnimatedSprite
	animationSprite = AnimatedSprite(0.2f, true, true);
    animationSprite.setPosition(mPosition);
	animationSprite.setOrigin(128, 128);
	animationSprite.play(*currentAnimation);
	mAnimStateMachine = std::make_shared<AnimationStateMachine<Higgins> >(AnimationStateMachine<Higgins>(this));
	mAnimStateMachine->SetCurrentState(HigginsIdle::Instance());
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
	defensiveQuad.setPosition(mPosition.x, mPosition.y);
	baseQuad.setPosition(mPosition.x, mPosition.y + 105);
	animationSprite.setPosition(mPosition.x, mPosition.y);

	window.draw(animationSprite);
	window.draw(baseQuad);
	window.draw(defensiveQuad);
}

void Higgins::Update(float timePassed)
{
	inputHandler.Update(timePassed);
	mAnimStateMachine->Update();
	animationSprite.Update(timePassed);
}

void Higgins::SetAnimIdle()
{
	mAnimStateMachine->ChangeState(HigginsIdle::Instance());
}

void Higgins::SetAnimRun()
{
	mAnimStateMachine->ChangeState(HigginsMove::Instance());
}