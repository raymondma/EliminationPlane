//
//  TFGun.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFGun.h"
#include "TFBulletBase.h"
#include "TFRole.h"
#include "TFTexturesCache.h"


DEFINE_DICTFUNC_STR(TFGun, BulletName);
DEFINE_DICTFUNC(TFGun, int, MaxLevel, 0);
DEFINE_DICTFUNC(TFGun, int, CacheNum, 0);
DEFINE_DICTFUNC(TFGun, float, Frequency, 0.f);


TFGun::TFGun() : m_lastShootTime(0)
,m_isDoubleBullet(false)
,m_frequency(0.f)
{
}



TFGun::~TFGun()
{
    clearThis();
}



bool TFGun::init(CCDictionary* pObjectDict)
{
    if (!TFObject::init(pObjectDict))
    {
        return false;
    }
    
    if (!TFBatchNodeObject::init())
    {
        return false;
    }
    
#ifdef DEBUG
    CCAssert(NULL != getBulletNameFromDict(), "BulletName must be set!");
#endif
    
    if (!container_.initCache(getBulletNameFromDict()->getCString(), getCacheNumFromDict()))
    {
        __CCLOGWITHFUNCTION("Bullet cache init failed. Gun: %s; Bullet: %s",
                            getNameFromDict()->getCString(), getBulletNameFromDict()->getCString());
        return false;
    }
    
    m_frequency = getFrequencyFromDict();
    m_lastShootTime = 0.f;
    return true;
}



void TFGun::update(float dt)
{    
    CCObject* pObj;
    const CCArray* children = container_.getInUseArray();
    CCArray needToCheckin;
    CCARRAY_FOREACH(children, pObj)
    {
        TFBulletBase* pBullet = dynamic_cast<TFBulletBase*>(pObj);
        if (pBullet != NULL && pBullet->isDead())
        {
            pBullet->removeSpriteFromParentAndCleanup(false);
            needToCheckin.addObject(pBullet);
        }
        else
        {
            pBullet->update(dt);
        }
    }
    
    CCARRAY_FOREACH(&needToCheckin, pObj)
    {
        container_.checkinElement(static_cast<TFObject*>(pObj));
    }
    needToCheckin.removeAllObjects();
}



void TFGun::setOwner(TFRole* role)
{
    CCAssert(role, "role is invalid.");
    
    if (role)
    {
        m_pRole = role;
    }
}



void TFGun::shoot(float dt)
{
    m_lastShootTime += dt;

    if (NULL == m_pRole)
    {
        __CCLOGWITHFUNCTION("make sure to call setOwner first!");
        return;
    }

    // rewrite later!!
//    CCPoint shootPoint = m_pRole->getSprite()->getParent()->convertToWorldSpace(m_pRole->getShootPoint());
    CCPoint shootPoint = m_pRole->getShootPoint();
    if (m_isDoubleBullet)
    {
        CCPoint offset[2] = {
            ccp(-10, 0),
            ccp(10, 0),
        };
        
        while (m_lastShootTime >= m_frequency)
        {
            m_lastShootTime -= m_frequency;
            
            for (int i=0; i<2; ++i)
            {
                TFBulletBase* pBullet = dynamic_cast<TFBulletBase*>(container_.checkoutElement());
                if (pBullet)
                {
                    pBullet->revive();
                    pBullet->setSpritePosition(ccpAdd(shootPoint, offset[i]));
                    pBullet->attachSpriteTo(getBatchNode());
                }
            }
        }
    }
    else
    {
        while (m_lastShootTime >= m_frequency)
        {
            m_lastShootTime -= m_frequency;
            

            TFBulletBase* pBullet = dynamic_cast<TFBulletBase*>(container_.checkoutElement());
            if (pBullet)
            {
                pBullet->revive();
                pBullet->setSpritePosition(ccpAdd(shootPoint, CCPointZero));
                pBullet->attachSpriteTo(getBatchNode());
            }

        }
    }
}



void TFGun::clearAll()
{
    TFObject::clearAll();
    clearThis();
}



void TFGun::clearThis()
{
    
}


bool TFGun::addBulletRow()
{
    m_isDoubleBullet = true;
    return true;
}



bool TFGun::removeBulletRow()
{
    m_isDoubleBullet = false;
    return true;
}



GameArts TFGun::getBatchNodeName()
{
    return GA_BULLETS;
}



bool TFGun::changeBullet(const string& name)
{
    container_.clear();
    if (!container_.initCache(name, getCacheNumFromDict()))
    {
        return false;
    }
    
    m_lastShootTime = 0.f;
    return true;
}
