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
	higgins->currentAnimation = &higgins->idleAnimation;
	higgins->animationSprite.setLooped(true);
	higgins->animationSprite.setFrameTime(0.2);
	higgins->animationSprite.play(*higgins->currentAnimation);
}

void HigginsIdle::Update(Higgins* higgins)
{
	if(higgins->moveLeft || higgins->moveRight)
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
	higgins->currentAnimation = &higgins->runAnimation;
	higgins->animationSprite.setLooped(true);
	higgins->animationSprite.setFrameTime(0.1);
	higgins->animationSprite.play(*higgins->currentAnimation);
}

void HigginsMove::Update(Higgins* higgins)
{
	if(!higgins->moveLeft && !higgins->moveRight)
	{
		higgins->SetAnimIdle();
	}
}

void HigginsMove::Exit(Higgins* higgins)
{
}