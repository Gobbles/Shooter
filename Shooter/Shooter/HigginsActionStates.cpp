#include "HigginsActionStates.h"
#include "Higgins.h"
#include <iostream>

//=====================================================================//
//-------------------HigginsWaiting Class Methods----------------------//
//=====================================================================//
HigginsWaiting* HigginsWaiting::Instance()
{
    static HigginsWaiting instance;
    
    return &instance;
}

void HigginsWaiting::Enter(Higgins* higgins)
{
	//intentionally blank
}

void HigginsWaiting::Update(Higgins* higgins, const float timePassed)
{
	//intentionally blank
}

void HigginsWaiting::Exit(Higgins* higgins)
{
	//intentionally blank
}

void HigginsWaiting::HandleInput(Higgins* higgins,const std::vector<bool> inputs)
{
	//inputs for attack/defend/other actions
	if(inputs[InputCommands::Input::Light_Attack] == true)
	{
		//we now change state to attack
		higgins->StartAttack();
	}
}

//=====================================================================//
//-------------------HigginsAttack Class Methods----------------------//
//=====================================================================//
HigginsAttack* HigginsAttack::Instance()
{
    static HigginsAttack instance;
    
    return &instance;
}

void HigginsAttack::Enter(Higgins* higgins)
{
	std::cout << "Entering Attack\n";
	chargeLevel = 0;
	removeTimer = 0.0f;
	onCooldown = false;
}

void HigginsAttack::Update(Higgins* higgins, const float timePassed)
{
	if(!onCooldown)
	{
		chargeLevel += 1 * timePassed;
		std::cout << "ChargeLevel: " << chargeLevel << "\n";
	}
	else
	{
		removeTimer += timePassed;
		if(removeTimer >= 0.2f)
		{
			higgins->RemoveAttack();
		}
	}
}

void HigginsAttack::Exit(Higgins* higgins)
{
}

void HigginsAttack::HandleInput(Higgins* higgins,const std::vector<bool> inputs)
{
	if(inputs[InputCommands::Input::Light_Attack] == false)
	{
		//we now change state to attack
		higgins->FireShot(chargeLevel);
		onCooldown = true;
	}

	if(onCooldown)
	{
		if(inputs[InputCommands::Input::Light_Attack] == true)
		{
			onCooldown = false;
			chargeLevel = 0;
			removeTimer = 0.0f;
		}
	}
}