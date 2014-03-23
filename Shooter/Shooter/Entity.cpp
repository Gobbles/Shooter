#include "Entity.h"

Entity::Entity(std::string fileLocation)
{
	inputHandler = InputHandler();
}

void Entity::CheckInput(sf::Event &event)
{ 
	bool checkCombos = false;
	InputCommands::Input input;
	if (event.type == sf::Event::JoystickButtonPressed)
	{
		std::cout << "joystick button pressed!" << std::endl;
		std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
		std::cout << "button: " << event.joystickButton.button << std::endl;
	}
	if (event.type == sf::Event::JoystickMoved)
	{
		if (event.joystickMove.axis == sf::Joystick::PovY)
		{
			std::cout << "X axis moved!" << std::endl;
			std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
			std::cout << "new position: " << event.joystickMove.position << std::endl;
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::A:
			{
				input = InputCommands::Input::Left;
				inputHandler.QueueInput(input);
				checkCombos = true;
				break;
			}
			case sf::Keyboard::D:
			{
				input = InputCommands::Input::Right;
				inputHandler.QueueInput(input);
				checkCombos = true;
				break;
			}
			case sf::Keyboard::W:
			{
				input = InputCommands::Input::Up;
				inputHandler.QueueInput(input);
				checkCombos = true;
				break;
			}
			case sf::Keyboard::S:
			{
				input = InputCommands::Input::Down;
				inputHandler.QueueInput(input);
				checkCombos = true;
				break;
			}
			case sf::Keyboard::Space:
			{
				input = InputCommands::Input::Jump;
				inputHandler.QueueInput(input);
				checkCombos = true;
				break;
			}
			case sf::Keyboard::Q:
			{
				input = InputCommands::Input::Light_Attack;
				inputHandler.QueueInput(input);
				checkCombos = true;
				break;
			}
			case sf::Keyboard::E:
			{
				input = InputCommands::Input::Heavy_Attack;
				inputHandler.QueueInput(input);
				checkCombos = true;
				break;
			}
		}
	}

	if(checkCombos == true)
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

int Entity::CheckCombos()
{
	system("cls");
	int size = inputHandler.GetSize();
	int currentKey = 0;
	if(size > 0)
	{
		for(int i = 0; i < 4; ++i) // check all the combos in order
		{
			currentKey = size - 1;
			for(int j = 4; j >= 0; --j)// check all the inputs in the combos in reverse order
			{
				if(Combos[i][j] == InputCommands::Input::Invalid)//instantly skip to the next input
					continue;

				if(currentKey < 0)
				{
					break; // break right away if our input to get is below 0 (the first element)
				}

				std::cout << "\nWe Have a proper check\n";

				InputCommands::Input inputToCheck = inputHandler.GetInput(currentKey);

				if(Combos[i][j] != inputToCheck)
					break;
				else if(j == 0) //we have the final input, we just completed a combo
					return i;
				else
					currentKey--;

			}
			std::cout << "\nNEXT COMBO\n";
		}
		return -1;
	}
}