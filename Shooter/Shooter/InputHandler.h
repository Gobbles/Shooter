#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <queue>
#include <iostream>
#include <SFML\Graphics.hpp>

namespace InputCommands
{
enum Input
{
	Invalid = -1,
	Up = 0,
	Down,
	Left,
	Right,
	Light_Attack,
	Heavy_Attack,
	Jump,
	Block,
	Ability_One,
	Ability_Two
};
}

/*REQUIRED:
-A timer to track time between inputs, this is to clear the input buffer between
pauses in input
- A way to track maximum Queue length
*/
class InputHandler
{
private:
	std::deque<InputCommands::Input> inputBuffer;

	void ClearInput(std::deque<InputCommands::Input> &queue);

	float timeSinceLastInput;
	bool runTimer;
public:
	InputHandler();
	void QueueInput(InputCommands::Input &input);
	void Update(float timePassed);
	InputCommands::Input GetInput(int index);
	int GetSize();
};

#endif