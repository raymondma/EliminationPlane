//
//  TFVisibleObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFVisibleObject.h"


DEFINE_DICTFUNC(TFVisibleObject, int, CollisionGroup, 0);


TFVisibleObject::TFVisibleObject() :
m_isCacheBoundingBox(false)
{
    
}



TFVisibleObject::~TFVisibleObject()
{
    clearThis();
}



void TFVisibleObject::update(float dt)
{
    TFObject::update(dt);
    
    updateBoundingBoxInWorldSpace();
}



void TFVisibleObject::updateBoundingBoxInWorldSpace()
{
    if (!m_isCacheBoundingBox)
    {
        return;
    }
    
    CCNode* pInnerSprite = getInnerSprite();
    
    m_boundingBoxInWorldSpace = getSpriteBoundingBox();
    
    if (NULL != pInnerSprite->getParent())
    {
        m_boundingBoxInWorldSpace.origin = pInnerSprite->getParent()->convertToWorldSpaceAR(m_boundingBoxInWorldSpace.origin);
    }
}



bool TFVisibleObject::isNeedCheckCollision()
{
    return TFObject::isNeedCheckCollision() && isSpriteVisible();
}



bool TFVisibleObject::isCollsionWith(TFCollisionProtocol* object)
{
    TFVisibleObject* pObj = dynamic_cast<TFVisibleObject*>(object);
    if (NULL == pObj)
    {
        return false;
    }
    
    CCRect b1 = getSpriteBoundingBoxInWorldSpace();
    CCRect b2 = pObj->getSpriteBoundingBoxInWorldSpace();
    
    return b1.intersectsRect(b2);
}




CCRect TFVisibleObject::getSpriteBoundingBox() const
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->boundingBox();
    }
    
    return CCRectZero;
}



CCRect TFVisibleObject::getSpriteBoundingBoxInWorldSpace()
{
    if (!m_isCacheBoundingBox)
    {
        CCNode* pInnerSprite = getInnerSprite();
        
        m_boundingBoxInWorldSpace = getSpriteBoundingBox();
        
        if (NULL != pInnerSprite->getParent())
        {
            m_boundingBoxInWorldSpace.origin = pInnerSprite->getParent()->convertToWorldSpaceAR(m_boundingBoxInWorldSpace.origin);
        }
    }
    
    return m_boundingBoxInWorldSpace;
}



CCPoint TFVisibleObject::getSpritePosition() const
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getPosition();
    }
    
    return CCPointZero;
}



void TFVisibleObject::setSpritePosition(const CCPoint& point)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setPosition(point);
    }
}



void TFVisibleObject::setSpriteVisible(bool visible)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setVisible(visible);
    }
}



bool TFVisibleObject::isSpriteVisible()
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->isVisible();
    }
    
    return false;
}




CCSize TFVisibleObject::getSpriteContentSize()
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getContentSize();
    }
    
    return CCSizeZero;
}



void TFVisibleObject::setSpriteZOrder(int z)
{
    if (NULL != getInnerSprite())
    {
        CCNode* pParent = getInnerSprite()->getParent();
        if (NULL != pParent)
        {
            getInnerSprite()->retain();
            pParent->removeChild(getInnerSprite(), false);
            pParent->addChild(getInnerSprite(), z);
            getInnerSprite()->release();
        }
    }
}



bool TFVisibleObject::isSpriteInScreen()
{
    if (NULL != getInnerSprite())
    {
        CCRect screen;
        screen.origin = CCPointZero;
        screen.size = CCDirector::sharedDirector()->getWinSize();
        if (screen.intersectsRect(getInnerSprite()->boundingBox()))
        {
            return true;
        }
    }
    
    return false;
}



void TFVisibleObject::setSpriteScaleX(float sx)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScaleX(sx);
    }
}



void TFVisibleObject::setSpriteScaleY(float sy)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScaleY(sy);
    }
}



void TFVisibleObject::setSpriteScale(float s)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScale(s);
    }
}



void TFVisibleObject::removeSpriteFromParentAndCleanup(bool cleanup)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->removeFromParentAndCleanup(cleanup);
    }
}



bool TFVisibleObject::runSpriteAction(CCAction* action)
{
    CCAssert(NULL != action, "action can't be NULL!");
    if (NULL == getInnerSprite())
    {
        return false;
    }

    getInnerSprite()->runAction(action);
    
    m_runningActions.addObject(action);
    return true;
}



void TFVisibleObject::stopSpriteAllActions()
{
    CCNode* node = getInnerSprite();
    
    if (node)
    {
        node->stopAllActions();
    }
}



void TFVisibleObject::setSpriteAnchorPoint(const CCPoint& point)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setAnchorPoint(point);
    }
}



bool TFVisibleObject::attachSpriteTo(CCNode* parent, int zOrder, int tag)
{
    CCAssert(NULL != parent, "parent can't be NULL");
    if (NULL != getInnerSprite())
    {
        parent->addChild(getInnerSprite(), zOrder, tag);
        return true;
    }
    return false;
}



int TFVisibleObject::getCollisionGroup()
{
    return getCollisionGroupFromDict();
}




void TFVisibleObject::turnOffCollision()
{
    TFObject::turnOffCollision();
    m_isCacheBoundingBox = false;
}



void TFVisibleObject::turnOnCollision()
{
    TFObject::turnOnCollision();
    m_isCacheBoundingBox = true;
}



void TFVisibleObject::die()
{
    TFObject::die();

    CCObject* pObj;
    CCARRAY_FOREACH(&m_runningActions, pObj)
    {
        if (NULL != getInnerSprite())
        {
            getInnerSprite()->stopAction(dynamic_cast<CCAction*>(pObj));
        }
    }
    m_runningActions.removeAllObjects();
}



void TFVisibleObject::revive()
{
    TFObject::revive();
}



void TFVisibleObject::clearThis()
{
    m_runningActions.removeAllObjects();
}



void TFVisibleObject::clearAll()
{
    TFObject::clearAll();
    
    clearThis();
}




