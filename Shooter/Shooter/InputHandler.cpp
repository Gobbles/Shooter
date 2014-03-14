#include "InputHandler.h"

void InputHandler::QueueInput(InputCommands::Input &input)
{
	inputBuffer.push(input);
	if(inputBuffer.size() > 120)
	{
		ClearInput(inputBuffer);
	}
	std::cout << inputBuffer.size();
}

void InputHandler::ClearInput(std::queue<InputCommands::Input> &queue)
{
	std::queue<InputCommands::Input> empty;
	std::swap(queue, empty);
}