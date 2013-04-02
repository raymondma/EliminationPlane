//
//  TFSpriteObject.h
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFSpriteObject__
#define __TheForce__TFSpriteObject__

#include "TFVisibleObject.h"
#include "TFSpriteActionDelegate.h"

class TFSpriteObject : public TFVisibleObject, public CCBAnimationManagerDelegate
{
    CC_SYNTHESIZE_RETAIN(CCBReader*, pCCBReader_, CCBReader);
public:
	virtual ~TFSpriteObject();
	
	virtual bool init(CCDictionary* pObjectDict);
    virtual void update(float dt);
    
    virtual void clearAll();

    virtual void revive();
    
    // Warning:DO NOT call changeState in the delegate function!
    virtual void setActionDelegate(TFSpriteActionDelegate* pDelegate);    

    virtual CCNode* getInnerSprite() const;

    virtual bool changeState(const string& s);
    virtual void changeStateOnAnimationLoopEnd(const string& s);
    virtual void endState();

//    virtual CCNode* getCCBReaderRootNode() const;
//    virtual void setContentSize(CCSize size);
    
    DECLARE_DICTFUNC(int, MaxLevel);
    DECLARE_DICTFUNC(CCString*, FileType);
    DECLARE_DICTFUNC(CCString*, FileName);
    DECLARE_DICTFUNC(CCString*, FileNameInFarm);
    DECLARE_DICTFUNC(CCString*, InitState);
    DECLARE_DICTFUNC(CCString*, FarmState);
    DECLARE_DICTFUNC(CCArray*, States);
    
protected:
    TFSpriteObject();
    void clearThis();
    
    virtual void setInnerSprite(CCSprite* var);
    virtual void completedAnimationSequenceNamed(const char *name);
    virtual void checkToChangeState();
    
    bool setSpriteFromCcbi(const char* name);
    bool setSprite(const char* name);
    
    TFSpriteActionDelegate* m_pActionDelegate;
private:
    CCSprite* pSprite_;
    bool isAnimationLoopEnd_;
    string nextState_;
};

#endif /* defined(__TheForce__TFSpriteObject__) */
