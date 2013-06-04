//
//  CVisibleObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CVisibleObject.h"


DEFINE_DICTFUNC(CVisibleObject, int, CollisionGroup, 0);


CVisibleObject::CVisibleObject() :
m_isCacheBoundingBox(false)
{
    
}



CVisibleObject::~CVisibleObject()
{
    clearThis();
}



void CVisibleObject::update(float dt)
{
    CObjectBase::update(dt);
    
    updateBoundingBoxInWorldSpace();
}



void CVisibleObject::updateBoundingBoxInWorldSpace()
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



bool CVisibleObject::isNeedCheckCollision()
{
    return CObjectBase::isNeedCheckCollision() && isSpriteVisible();
}



bool CVisibleObject::isCollsionWith(TFCollisionProtocol* object)
{
    CVisibleObject* pObj = dynamic_cast<CVisibleObject*>(object);
    if (NULL == pObj)
    {
        return false;
    }
    
    CCRect b1 = getSpriteBoundingBoxInWorldSpace();
    CCRect b2 = pObj->getSpriteBoundingBoxInWorldSpace();
    
    return b1.intersectsRect(b2);
}




CCRect CVisibleObject::getSpriteBoundingBox() const
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->boundingBox();
    }
    
    return CCRectZero;
}



CCRect CVisibleObject::getSpriteBoundingBoxInWorldSpace()
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



CCPoint CVisibleObject::getSpritePosition() const
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getPosition();
    }
    
    return CCPointZero;
}



void CVisibleObject::setSpritePosition(const CCPoint& point)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setPosition(point);
    }
}



void CVisibleObject::setSpriteVisible(bool visible)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setVisible(visible);
    }
}



bool CVisibleObject::isSpriteVisible()
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->isVisible();
    }
    
    return false;
}




CCSize CVisibleObject::getSpriteContentSize()
{
    if (NULL != getInnerSprite())
    {
        return getInnerSprite()->getContentSize();
    }
    
    return CCSizeZero;
}



void CVisibleObject::setSpriteZOrder(int z)
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



bool CVisibleObject::isSpriteInScreen()
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



void CVisibleObject::setSpriteScaleX(float sx)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScaleX(sx);
    }
}



void CVisibleObject::setSpriteScaleY(float sy)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScaleY(sy);
    }
}



void CVisibleObject::setSpriteScale(float s)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setScale(s);
    }
}



void CVisibleObject::removeSpriteFromParentAndCleanup(bool cleanup)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->removeFromParentAndCleanup(cleanup);
    }
}



bool CVisibleObject::runSpriteAction(CCAction* action)
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



void CVisibleObject::stopSpriteAllActions()
{
    CCNode* node = getInnerSprite();
    
    if (node)
    {
        node->stopAllActions();
    }
}



void CVisibleObject::setSpriteAnchorPoint(const CCPoint& point)
{
    if (NULL != getInnerSprite())
    {
        getInnerSprite()->setAnchorPoint(point);
    }
}



bool CVisibleObject::attachSpriteTo(CCNode* parent, int zOrder, int tag)
{
    CCAssert(NULL != parent, "parent can't be NULL");
    if (NULL != getInnerSprite())
    {
        parent->addChild(getInnerSprite(), zOrder, tag);
        return true;
    }
    return false;
}



int CVisibleObject::getCollisionGroup()
{
    return getCollisionGroupFromDict();
}




void CVisibleObject::turnOffCollision()
{
    CObjectBase::turnOffCollision();
    m_isCacheBoundingBox = false;
}



void CVisibleObject::turnOnCollision()
{
    CObjectBase::turnOnCollision();
    m_isCacheBoundingBox = true;
}



void CVisibleObject::die()
{
    CObjectBase::die();

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



void CVisibleObject::revive()
{
    CObjectBase::revive();
}



void CVisibleObject::clearThis()
{
    m_runningActions.removeAllObjects();
}



void CVisibleObject::clearAll()
{
    CObjectBase::clearAll();
    
    clearThis();
}




