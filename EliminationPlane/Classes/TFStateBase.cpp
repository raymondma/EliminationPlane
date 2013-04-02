//
//  TFStateBase.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-24.
//
//

#include "TFStateBase.h"

TFStateBase::TFStateBase() :
isStateLocked_(false)
{
	
}



TFStateBase::~TFStateBase()
{
	
}



string TFStateBase::getCurrentState() const
{
	return currentState_;
}



bool TFStateBase::changeState(const string& s)
{
    if (isStateLocked_ || s.compare(currentState_) == 0)
    {
        return false;
    }
    
	if(!currentState_.empty())
    {
        leaveState(currentState_);
    }
	
	currentState_ = s;
	
	enterState(currentState_);
	return true;
}



void TFStateBase::enterState(const string& s)
{
    
}



void TFStateBase::leaveState(const string& s)
{
	
}



void TFStateBase::lockState()
{
    isStateLocked_ = true;
}



void TFStateBase::unlockState()
{
    isStateLocked_ = false;
}



void TFStateBase::clearState()
{
    unlockState();
    currentState_.clear();
}