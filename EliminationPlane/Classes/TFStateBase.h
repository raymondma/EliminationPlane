//
//  TFStateBase.h
//  TheForce
//
//  Created by 马 俊 on 13-1-24.
//
//

#ifndef __TheForce__TFStateBase__
#define __TheForce__TFStateBase__

#include <string>
#include <vector>

using namespace std;

class TFStateBase
{
public:
	TFStateBase();
	virtual ~TFStateBase();
	
	virtual string getCurrentState() const;
	virtual bool changeState(const string& s);

    
    virtual void lockState();
    virtual void unlockState();
protected:
	virtual void enterState(const string& s);
	virtual void leaveState(const string& s);
	virtual void clearState();
private:
    string currentState_;
    bool isStateLocked_;
};

#endif /* defined(__TheForce__TFStateBase__) */
