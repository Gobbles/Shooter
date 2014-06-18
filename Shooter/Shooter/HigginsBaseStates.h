#ifndef HIGGINS_BASE_STATES_H
#define HIGGINS_BASE_STATES_H

#include "State.h"
#include <vector>

class Higgins;

//=======================
//Higgins Idle State
//=======================
class HigginsIdle : public State<Higgins>
{
private:
    HigginsIdle() { }

    HigginsIdle(const HigginsIdle&);

    HigginsIdle& operator=(const HigginsIdle&);
public:

    static HigginsIdle* Instance();

    virtual void Enter(Higgins* higgins);

    virtual void Update(Higgins* higgins, const float timePassed);

    virtual void Exit(Higgins* higgins);

	virtual void HandleInput(Higgins* higgins, const std::vector<bool> inputs);
};

//=======================
//Higgins Move State
//=======================
class HigginsMove : public State<Higgins>
{
private:
    HigginsMove() { }

    HigginsMove(const HigginsMove&);

    HigginsMove& operator=(const HigginsMove&);
public:
    
    static HigginsMove* Instance();

    virtual void Enter(Higgins* higgins);

    virtual void Update(Higgins* higgins, const float timePassed);

    virtual void Exit(Higgins* higgins);

	virtual void HandleInput(Higgins* higgins,const std::vector<bool> inputs);
};
#endif