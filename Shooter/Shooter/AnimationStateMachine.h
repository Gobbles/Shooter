#ifndef ANIMATION_STATE_MACHINE_H
#define ANIMATION_STATE_MACHINE_H

#include "State.h"
#include <cassert>

template <class entity_type>
class AnimationStateMachine
{
private:
    entity_type* mOwner;

    //Current State we are in
    State<entity_type>* mCurrentState;

    //Previous State we were just in
    State<entity_type>* mPreviousState;

    //Global State we are in
    State<entity_type>* mGlobalState;

public:
    AnimationStateMachine(entity_type* owner):mOwner(owner),
    mCurrentState(NULL),
    mPreviousState(NULL),
    mGlobalState(NULL)
    {
		std::cout << "Build Machine\n";
	}

    virtual ~AnimationStateMachine() {}

    void SetCurrentState(State<entity_type>* s) {mCurrentState = s;}
    void SetGlobalState(State<entity_type>* s) {mGlobalState = s;}
    void SetPreviousState(State<entity_type>* s){mPreviousState = s;}

    void Update()const
    {
        if(mGlobalState)
            mGlobalState->Update(mOwner);

        if(mCurrentState)
            mCurrentState->Update(mOwner);
    }

    void ChangeState(State<entity_type>* pNewState)
    {
        assert(pNewState && "<AnimationStateMachine::ChangeState>: trying to change to a null state");

        //Store our current State as our previous state
        mPreviousState = mCurrentState;

        //Exit out of our current State
        mCurrentState->Exit(mOwner);
        
        //Set our new current state
        SetCurrentState(pNewState);

        //Enter the state
        mCurrentState->Enter(mOwner);

    }

    void RevertToPreviousState()
    {
        ChangeState(mPreviousState);
    }

    //state accessors
    State<entity_type>* CurrentState() const {return mCurrentState;}
    State<entity_type>* GlobalState() const {return mGlobalState;}
    State<entity_type>* PreviousState() const {return mPreviousState;}

    //check our current state
    bool isInState(State<entity_type>* st)
    {
        if( st == mCurrentState)
            return true;

        return false;
    }
};

#endif