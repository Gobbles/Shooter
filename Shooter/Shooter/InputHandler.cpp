#include "InputHandler.h"

InputHandler::InputHandler()
{
	timeSinceLastInput = 0;
	runTimer = false;
}
void InputHandler::QueueInput(InputCommands::Input &input)
{
	inputBuffer.push_back(input);
	timeSinceLastInput = 0.0;
	if(runTimer == false)
	{
		runTimer = true;
	}
	if(inputBuffer.size() > 120)
	{
		ClearInput(inputBuffer);
	}
	std::cout << inputBuffer.size();
}

void InputHandler::ClearInput(std::deque<InputCommands::Input> &queue)
{
	std::deque<InputCommands::Input> empty;
	std::swap(queue, empty);
}

void InputHandler::Update(float timePassed)
{
	if(runTimer == true)
	{
		timeSinceLastInput += timePassed;

		if(timeSinceLastInput > 0.6)
		{
			std::cout << "Reset Input";
			ClearInput(inputBuffer);
			timeSinceLastInput = 0.0;
			runTimer = false;
		}
	}
}

InputCommands::Input InputHandler::GetInput(int index)
{
	return inputBuffer[index];
}

int InputHandler::GetSize()
{
	return inputBuffer.size();
}