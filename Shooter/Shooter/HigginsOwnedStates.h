#ifndef HIGGINS_OWNED_STATES_H
#define HIGGINS_OWNED_STATES_H

#include "State.h"

class Higgins;

class HigginsIdle : public State<Higgins>
{
private:
    HigginsIdle() { }

    HigginsIdle(const HigginsIdle&);

    HigginsIdle& operator=(const HigginsIdle&);
public:

    static HigginsIdle* Instance();

    virtual void Enter(Higgins* higgins);

    virtual void Update(Higgins* higgins);

    virtual void Exit(Higgins* higgins);
};


class HigginsMove : public State<Higgins>
{
private:
    HigginsMove() { }

    HigginsMove(const HigginsMove&);

    HigginsMove& operator=(const HigginsMove&);
public:
    
    static HigginsMove* Instance();

    virtual void Enter(Higgins* higgins);

    virtual void Update(Higgins* higgins);

    virtual void Exit(Higgins* higgins);
};

#endif