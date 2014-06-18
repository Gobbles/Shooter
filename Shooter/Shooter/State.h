#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

template <class entity_type>
class State
{
public:
    //this will execute when the state is entered
    virtual void Enter(entity_type*)=0;
    //this is called by the state machines update function each update step
	virtual void Update(entity_type*, const float timePassed)=0;
    //this will execute when the state is exited
    virtual void Exit(entity_type*)=0;
	//handling of any inputs
	virtual void HandleInput(entity_type*,const std::vector<bool> inputs)=0;
};

#endif 