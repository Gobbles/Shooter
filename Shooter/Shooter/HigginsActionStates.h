#ifndef HIGGINS_ACTION_STATES_H
#define HIGGINS_ACTION_STATES_H

#include "State.h"
#include <vector>

class Higgins;

//=======================
//Higgins Waiting State - this states sole purpose is to wait for any input and switch
// to the appropriate action state. we go back here when the player has no actions
//=======================
class HigginsWaiting : public State<Higgins>
{
private:
    HigginsWaiting() { }

    HigginsWaiting(const HigginsWaiting&);

    HigginsWaiting& operator=(const HigginsWaiting&);

public:
    
    static HigginsWaiting* Instance();

    virtual void Enter(Higgins* higgins);

    virtual void Update(Higgins* higgins, const float timePassed);

    virtual void Exit(Higgins* higgins);

	virtual void HandleInput(Higgins* higgins,const std::vector<bool> inputs);
};

//=======================
//Higgins Attack State
//=======================
class HigginsAttack : public State<Higgins>
{
private:
    HigginsAttack() { }

    HigginsAttack(const HigginsAttack&);

    HigginsAttack& operator=(const HigginsAttack&);

	//members
	float chargeLevel;
	bool onCooldown;
	float removeTimer;

public:
    
    static HigginsAttack* Instance();

    virtual void Enter(Higgins* higgins);

    virtual void Update(Higgins* higgins, const float timePassed);

    virtual void Exit(Higgins* higgins);

	virtual void HandleInput(Higgins* higgins,const std::vector<bool> inputs);
};

#endif