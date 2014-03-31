#ifndef STATE_H
#define STATE_H

#include <memory>

template <class entity_type>
class State
{
public:
    //this will execute when the state is entered
    virtual void Enter(entity_type*)=0;
    //this is called by the state machines update function each update step
    virtual void Update(entity_type*)=0;
    //this will execute when the state is exited
    virtual void Exit(entity_type*)=0;
};

#endif 