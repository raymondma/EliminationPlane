//
//  CSpriteObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CSpriteObject.h"


DEFINE_DICTFUNC(CSpriteObject, int, MaxLevel, 0);
DEFINE_DICTFUNC_STR(CSpriteObject, FileType);
DEFINE_DICTFUNC_STR(CSpriteObject, FileName);
DEFINE_DICTFUNC_STR(CSpriteObject, FileNameInFarm);
DEFINE_DICTFUNC_STR(CSpriteObject, InitState);
DEFINE_DICTFUNC_STR(CSpriteObject, FarmState);
DEFINE_DICTFUNC_ARRAY(CSpriteObject, States);

CSpriteObject::CSpriteObject()
: pSprite_(NULL)
, pCCBReader_(NULL)
, m_pActionDelegate(NULL)
, isAnimationLoopEnd_(false)
{
    
}



CSpriteObject::~CSpriteObject()
{
    clearThis();
}



bool CSpriteObject::init(CCDictionary* pObjectDict)
{
    do {
        CC_BREAK_IF(!CObjectBase::init(pObjectDict));
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


bool CSpriteObject::setSpriteFromCcbi(const char* name)
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


bool CSpriteObject::setSprite(const char* name)
{
    setInnerSprite(CCSprite::createWithSpriteFrameName(name));
    
    if (NULL == getInnerSprite())
    {
        return false;
    }
    setCCBReader(NULL);
    return true;
}


//void CSpriteObject::setContentSize(CCSize size)
//{
//    CVisibleObject::setContentSize(size);
//    
//    if (m_pSprite)
//    {
//        m_pSprite->setContentSize(size);
//    }
//}


//void CSpriteObject::setCCBReaderRootContainerSize(CCSize size)
//{
//    if (pCCBReader_)
//    {
////        pCCBReader_->getAnimationManager()->setRootContainerSize(size);
//    }
//}


void CSpriteObject::setActionDelegate(CSpriteActionDelegate* pDelegate)
{
    CC_SAFE_RELEASE(dynamic_cast<CCObject*>(m_pActionDelegate));
    m_pActionDelegate = pDelegate;
    CC_SAFE_RETAIN(dynamic_cast<CCObject*>(m_pActionDelegate));
}


void CSpriteObject::clearAll()
{
    CObjectBase::clearAll();
 
    clearThis();
}



void CSpriteObject::clearThis()
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



bool CSpriteObject::changeState(const string& s, CComponentParameter* parameter, bool force)
{
    if (!CVisibleObject::changeState(s, parameter, force))
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


void CSpriteObject::endState()
{
    this->changeState("");
}


CCNode* CSpriteObject::getInnerSprite() const
{
    return pSprite_;
}



void CSpriteObject::setInnerSprite(CCSprite* var)
{
    if (pSprite_ != var)
    {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(pSprite_);
        pSprite_ = var;
    } 
}


//CCNode* CSpriteObject::getCCBReaderRootNode() const
//{
//    if (pCCBReader_)
//    {
//        return pCCBReader_->getAnimationManager()->getRootNode();
//    }
//    
//    return NULL;
//}




void CSpriteObject::revive()
{
    CVisibleObject::revive();
    
    CCString* initState = getInitStateFromDict();
    if (initState != NULL)
    {
        changeState(getInitStateFromDict()->getCString());
    }

}

void CSpriteObject::completedAnimationSequenceNamed(const char *name)
{
    if (m_pActionDelegate)
    {
        m_pActionDelegate->completedAction(this, name);
    }
    
    isAnimationLoopEnd_ = true;
    
}



void CSpriteObject::changeStateOnAnimationLoopEnd(const string& s)
{
    nextState_ = s;
}



void CSpriteObject::checkToChangeState()
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



void CSpriteObject::update(float dt)
{
    CVisibleObject::update(dt);
    checkToChangeState();
}

