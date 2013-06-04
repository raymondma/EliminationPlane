//
//  EPPlane.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-4-1.
//
//

#include "EPPlane.h"

EPPlane::EPPlane() :
m_isDoubleGun(false)
, m_doubleGunStartTime(-1.f)
, m_doubleGunDuration(0)
{
    
}



EPPlane::~EPPlane()
{
    
}



void EPPlane::update(float dt)
{
    CRole::update(dt);
    updateDoubleGun(dt);
}



void EPPlane::updateDoubleGun(float dt)
{
    if (m_isDoubleGun)
    {
        if ( FLT_LE(m_doubleGunStartTime, 0.f))
        {
            m_doubleGunStartTime = 0;
        }
        m_doubleGunStartTime += dt;
        
        if (FLT_GE(m_doubleGunStartTime, m_doubleGunDuration))
        {
            cancelDoubleGun();
        }
    }
}



void EPPlane::clearAll()
{
    CRole::clearAll();
    
    clearThis();
}



void EPPlane::clearThis()
{
    
}



void EPPlane::triggerSkill()
{
    
}



void EPPlane::MoveDelta(float x)
{
    CCPoint pt = getSpritePosition();
    pt.x += x;
    CCSize winSz = CCDirector::sharedDirector()->getWinSize();
    CCSize bx = getSpriteBoundingBox().size;
    float halfWidth = bx.width / 2.f;
    
    if (pt.x < halfWidth)
    {
        pt.x = halfWidth;
    }
    else if (pt.x >= winSz.width-halfWidth)
    {
        pt.x = winSz.width-halfWidth;
    }
    setSpritePosition(pt);
}



void EPPlane::doubleGun(float duration)
{
    if (NULL != getGun())
    {
        getGun()->addBulletRow();
    }
    m_isDoubleGun = true;
    m_doubleGunStartTime = -1.f;
    m_doubleGunDuration = duration;
}



void EPPlane::cancelDoubleGun()
{
    if (NULL != getGun())
    {
        getGun()->removeBulletRow();
    }
    m_isDoubleGun = false;
    m_doubleGunStartTime = -1.f;
}



void EPPlane::checkCollision(TFCollisionProtocol* rb)
{
    
}



