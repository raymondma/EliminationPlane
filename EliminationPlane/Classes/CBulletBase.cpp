//
//  CBulletBase.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#include "CBulletBase.h"
#include "CRole.h"
#include "TFMonster.h"

#include "TFPListReaderHelper.h"
#include "Common.h"

DEFINE_DICTFUNC(CBulletBase, float, Damage, 0.f);
DEFINE_DICTFUNC(CBulletBase, float, Speed, 0.f);

CBulletBase::CBulletBase() :
m_speed(0.f)
{
    
}



CBulletBase::~CBulletBase()
{
    
}



bool CBulletBase::init(CCDictionary* pObjectDict)
{
    if (!CSpriteObject::init(pObjectDict))
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



void CBulletBase::checkCollision(TFCollisionProtocol* rb)
{
    TFMonster* pMonster = dynamic_cast<TFMonster*>(rb);
    if (pMonster)
    {
        die();
    }
}



void CBulletBase::update(float dt)
{
    CSpriteObject::update(dt);
    
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



float CBulletBase::getDamage()
{
    return getDamageFromDict();
}




