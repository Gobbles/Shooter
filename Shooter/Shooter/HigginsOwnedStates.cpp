#include "HigginsOwnedStates.h"
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

void HigginsIdle::Update(Higgins* higgins)
{
	if(higgins->moveLeft || higgins->moveRight || higgins->moveUp || higgins->moveDown)
	{
		higgins->SetAnimRun();
	}
}

void HigginsIdle::Exit(Higgins* higgins)
{
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

void HigginsMove::Update(Higgins* higgins)
{
	if(!higgins->moveLeft && !higgins->moveRight && !higgins->moveUp && !higgins->moveDown)
	{
		higgins->SetAnimIdle();
	}
	//if our last time is greater then our endtime
	//if(higgins->drawable->state->tracks[0]->lastTime > higgins->drawable->state->tracks[0]->endTime)
}

void HigginsMove::Exit(Higgins* higgins)
{
}