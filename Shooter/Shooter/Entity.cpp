#include "Entity.h"

Entity::Entity(std::string fileLocation)
{
	inputHandler = InputHandler();
}

void Entity::CheckInput(sf::Event &event)
{
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
				break;
			}
			case sf::Keyboard::D:
			{
				break;
			}
			case sf::Keyboard::W:
			{
				break;
			}
			case sf::Keyboard::S:
			{
				break;
			}
			case sf::Keyboard::Space:
			{
				break;
			}
			case sf::Keyboard::Q:
			{
				break;
			}
			case sf::Keyboard::E:
			{
				break;
			}
		}
	}
}