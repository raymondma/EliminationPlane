//
//  TFSpriteObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFSpriteObject.h"


DEFINE_DICTFUNC(TFSpriteObject, int, MaxLevel, 0);
DEFINE_DICTFUNC_STR(TFSpriteObject, FileType);
DEFINE_DICTFUNC_STR(TFSpriteObject, FileName);
DEFINE_DICTFUNC_STR(TFSpriteObject, FileNameInFarm);
DEFINE_DICTFUNC_STR(TFSpriteObject, InitState);
DEFINE_DICTFUNC_STR(TFSpriteObject, FarmState);
DEFINE_DICTFUNC_ARRAY(TFSpriteObject, States);

TFSpriteObject::TFSpriteObject()
: pSprite_(NULL)
, pCCBReader_(NULL)
, m_pActionDelegate(NULL)
, isAnimationLoopEnd_(false)
{
    
}



TFSpriteObject::~TFSpriteObject()
{
    clearThis();
}



bool TFSpriteObject::init(CCDictionary* pObjectDict)
{
    do {
        CC_BREAK_IF(!TFObject::init(pObjectDict));
        CCString* fileType = getFileTypeFromDict();
        CC_BREAK_IF(NULL == fileType);
        CCString* fileName = getFileNameFromDict();
        CC_BREAK_IF(NULL == fileName);
        
        if (getMaxLevelFromDict() > 0)
        {
            fileName = CCString::createWithFormat("%s%d", fileName->getCString(), getLevel() - 1);
        }
        
        if (fileType->compare("ccbi") == 0)
        {
            fileName = CCString::createWithFormat("%s.ccbi", fileName->getCString());
            CC_BREAK_IF(!setSpriteFromCcbi(fileName->getCString()));
        }
        else
        {
            CC_BREAK_IF(!setSprite(fileName->getCString()));
        }
        
        return true;
    } while (false);
    
    return false;
}


bool TFSpriteObject::setSpriteFromCcbi(const char* name)
{
    // Create auto-release node loader
    CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

    // Create a CCBReader, auto release.
    CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();

    // Read a ccbi file, return a CCNode instance.
    setInnerSprite(dynamic_cast<CCSprite*>(ccbReader->readNodeGraphFromFile(name, this)));

    if (NULL == getInnerSprite())
    {
        return false;
    }

    ccbReader->getAnimationManager()->setDelegate(this);
    
    setCCBReader(ccbReader);
    return true;
}


bool TFSpriteObject::setSprite(const char* name)
{
    setInnerSprite(CCSprite::createWithSpriteFrameName(name));
    
    if (NULL == getInnerSprite())
    {
        return false;
    }
    setCCBReader(NULL);
    return true;
}


//void TFSpriteObject::setContentSize(CCSize size)
//{
//    TFVisibleObject::setContentSize(size);
//    
//    if (m_pSprite)
//    {
//        m_pSprite->setContentSize(size);
//    }
//}


//void TFSpriteObject::setCCBReaderRootContainerSize(CCSize size)
//{
//    if (pCCBReader_)
//    {
////        pCCBReader_->getAnimationManager()->setRootContainerSize(size);
//    }
//}


void TFSpriteObject::setActionDelegate(TFSpriteActionDelegate* pDelegate)
{
    CC_SAFE_RELEASE(dynamic_cast<CCObject*>(m_pActionDelegate));
    m_pActionDelegate = pDelegate;
    CC_SAFE_RETAIN(dynamic_cast<CCObject*>(m_pActionDelegate));
}


void TFSpriteObject::clearAll()
{
    TFObject::clearAll();
 
    clearThis();
}



void TFSpriteObject::clearThis()
{
    CCBReader* pCCBReader = getCCBReader();
    if (pCCBReader)
    {
        pCCBReader->getAnimationManager()->setDelegate(NULL);
    }
    setCCBReader(NULL);
    setActionDelegate(NULL);
    
    if (pSprite_ != NULL)
    {
        pSprite_->removeFromParentAndCleanup(true);
        setInnerSprite(NULL);
    }
}



bool TFSpriteObject::changeState(const string& s)
{
    if (!TFVisibleObject::changeState(s))
    {
        return false;
    }
    
    if (s.empty())
    {
        getInnerSprite()->stopAllActions();
    }
    else
    {
        if (getCCBReader())
        {
            getCCBReader()->getAnimationManager()->runAnimations(s.c_str());
        }
    }
    
    return true;
}


void TFSpriteObject::endState()
{
    this->changeState("");
}


CCNode* TFSpriteObject::getInnerSprite() const
{
    return pSprite_;
}



void TFSpriteObject::setInnerSprite(CCSprite* var)
{
    if (pSprite_ != var)
    {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(pSprite_);
        pSprite_ = var;
    } 
}


//CCNode* TFSpriteObject::getCCBReaderRootNode() const
//{
//    if (pCCBReader_)
//    {
//        return pCCBReader_->getAnimationManager()->getRootNode();
//    }
//    
//    return NULL;
//}




void TFSpriteObject::revive()
{
    TFVisibleObject::revive();
    
    CCString* initState = getInitStateFromDict();
    if (initState != NULL)
    {
        changeState(getInitStateFromDict()->getCString());
    }

}

void TFSpriteObject::completedAnimationSequenceNamed(const char *name)
{
    if (m_pActionDelegate)
    {
        m_pActionDelegate->completedAction(this, name);
    }
    
    isAnimationLoopEnd_ = true;
    
}



void TFSpriteObject::changeStateOnAnimationLoopEnd(const string& s)
{
    nextState_ = s;
}



void TFSpriteObject::checkToChangeState()
{
    if (isAnimationLoopEnd_)
    {
        isAnimationLoopEnd_ = false;
        if (!nextState_.empty())
        {
            changeState(nextState_);
            nextState_.clear();
        }
    }
}



void TFSpriteObject::update(float dt)
{
    TFVisibleObject::update(dt);
    checkToChangeState();
}

