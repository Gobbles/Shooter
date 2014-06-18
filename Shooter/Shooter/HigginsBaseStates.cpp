#include "HigginsBaseStates.h"
#include "Higgins.h"
#include <iostream>

//-------------------HigginsIdle Class Methods----------------------//
HigginsIdle* HigginsIdle::Instance()
{
    static HigginsIdle instance;
    
    return &instance;
}

void HigginsIdle::Enter(Higgins* higgins)
{
	std::cout << "Entering Idle\n";
}

void HigginsIdle::Update(Higgins* higgins, const float timePassed)
{
	
}

void HigginsIdle::Exit(Higgins* higgins)
{
}

void HigginsIdle::HandleInput(Higgins* higgins,const std::vector<bool> inputs)
{
	if(inputs[InputCommands::Input::Up] || inputs[InputCommands::Input::Down] || inputs[InputCommands::Input::Left] || inputs[InputCommands::Input::Right])
	{
		higgins->SetAnimRun();
	}
}

//-------------------HigginsMove Class Methods----------------------//

HigginsMove* HigginsMove::Instance()
{
    static HigginsMove instance;
    
    return &instance;
}

void HigginsMove::Enter(Higgins* higgins)
{

	std::cout << "Entering Move\n";
}

void HigginsMove::Update(Higgins* higgins, const float timePassed)
{
	/*if(!higgins->moveLeft && !higgins->moveRight && !higgins->moveUp && !higgins->moveDown)
	{
		higgins->SetAnimIdle();
	}*/
	//if our last time is greater then our endtime
	//if(higgins->drawable->state->tracks[0]->lastTime > higgins->drawable->state->tracks[0]->endTime)
}

void HigginsMove::Exit(Higgins* higgins)
{
}

void HigginsMove::HandleInput(Higgins* higgins,const std::vector<bool> inputs)
{
	if(inputs[InputCommands::Input::Up])
	{
		higgins->mVelocity.y = -300;
	}
	else if(inputs[InputCommands::Input::Down])
	{
		higgins->mVelocity.y = 300;
	}
	if(inputs[InputCommands::Input::Left])
	{
		higgins->FlipSkeleton(true);
		higgins->mVelocity.x = -300;
	}
	else if(inputs[InputCommands::Input::Right])
	{
		higgins->FlipSkeleton(false);
		higgins->mVelocity.x = 300;
	}
	if(!inputs[InputCommands::Input::Up] && !inputs[InputCommands::Input::Down] && !inputs[InputCommands::Input::Left] && !inputs[InputCommands::Input::Right])
	{
		higgins->SetAnimIdle();
	}
}

