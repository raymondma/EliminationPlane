//
//  TFBulletBase.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#include "TFBulletBase.h"
#include "TFRole.h"
#include "TFMonster.h"

#include "TFPListReaderHelper.h"
#include "Common.h"

DEFINE_DICTFUNC(TFBulletBase, float, Damage, 0.f);
DEFINE_DICTFUNC(TFBulletBase, float, Speed, 0.f);

TFBulletBase::TFBulletBase() :
m_speed(0.f)
{
    
}



TFBulletBase::~TFBulletBase()
{
    
}



bool TFBulletBase::init(CCDictionary* pObjectDict)
{
    if (!TFSpriteObject::init(pObjectDict))
    {
        return false;
    }
    
    m_speed = getSpeedFromDict();
    if (FLT_EQUAL(m_speed, 0.f))
    {
        __CCLOGWITHFUNCTION("Bullet's speed is not set or set to 0.bulletname: %s", getNameFromDict());
        return false;
    }
    
    return true;
}



void TFBulletBase::checkCollision(TFCollisionProtocol* rb)
{
    TFMonster* pMonster = dynamic_cast<TFMonster*>(rb);
    if (pMonster)
    {
        die();
    }
}



void TFBulletBase::update(float dt)
{
    TFSpriteObject::update(dt);
    
    if (!isDead())
    {
        float offset = m_speed * dt;
        CCPoint pt = getSpritePosition();
        pt.y += offset;
        setSpritePosition(pt);
        
        CCSize winSz = CCDirector::sharedDirector()->getWinSize();
        if (pt.y > winSz.height + 30)
        {
            die();
        }
    }
}



float TFBulletBase::getDamage()
{
    return getDamageFromDict();
}




