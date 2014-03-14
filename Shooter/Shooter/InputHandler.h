#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <queue>
#include <iostream>
#include <SFML\Graphics.hpp>

namespace InputCommands
{
enum Input
{
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
	std::queue<InputCommands::Input> inputBuffer;

	void ClearInput(std::queue<InputCommands::Input> &queue);
public:	
	void QueueInput(InputCommands::Input &input);
};

#endif