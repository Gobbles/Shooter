#include "Higgins.h"

Higgins::Higgins() : Entity("")
{
	mPosition = sf::Vector2f(400,400);

	baseQuad = sf::RectangleShape(sf::Vector2f(100,35));
	baseQuad.setOrigin(baseQuad.getSize().x/2,baseQuad.getSize().y/2);
	baseQuad.setFillColor(sf::Color(0,0,255,64));

	defensiveQuad = sf::RectangleShape(sf::Vector2f(80,130));
	defensiveQuad.setOrigin(defensiveQuad.getSize().x/2,defensiveQuad.getSize().y/2);
	defensiveQuad.setFillColor(sf::Color(0,255,0,64));
	BuildCombos();
}

Higgins::~Higgins()
{
	
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

void Higgins::Draw(sf::RenderWindow& window)
{
	//set quad positions
	defensiveQuad.setPosition(mPosition.x, mPosition.y - 55);
	baseQuad.setPosition(mPosition.x, mPosition.y);

	window.draw(baseQuad);
	window.draw(defensiveQuad);
}

void Higgins::Update(float timePassed)
{
	inputHandler.Update(timePassed);
}