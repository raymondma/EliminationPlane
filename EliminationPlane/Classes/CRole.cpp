//
//  CRole.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//
#include "CRole.h"
#include "CBulletBase.h"
#include "TFGameObjectManager.h"


DEFINE_DICTFUNC_DICTIONARY(CRole, Gun);




CRole::CRole() : m_pGun(NULL)
{

}



CRole::~CRole()
{
    clearThis();
}



bool CRole::init(CCDictionary* pObjectDict)
{
    if (!CSpriteObject::init(pObjectDict))
    {
        return false;
    }
    
    CCDictionary* pGunDict = getGunFromDict();
    if (NULL != pGunDict )
    {
        CCString* str = dynamic_cast<CCString*>(pGunDict->objectForKey("ShootPoint"));
        if (NULL == str)
        {
            __CCLOGWITHFUNCTION("ShootPoint not found in Gun of GameObject: %s", getNameFromDict()->getCString());
            return false;
        }
        m_shootPoint = CCPointFromString(str->getCString());
        
        str = dynamic_cast<CCString*>(pGunDict->objectForKey("GunName"));
        if (NULL == str)
        {
            __CCLOGWITHFUNCTION("GunName not found in Gun of GameObject: %s", getNameFromDict()->getCString());
            return false;
        }
        
        if (!createGun(str->getCString()))
        {
            __CCLOGWITHFUNCTION("create default gun failed");
            return false;
        }
    }
    
	return true;
}



CCPoint CRole::getShootPoint()
{
//    return ccpAdd(getSpritePosition(), m_shootPoint);
    return m_shootPointInWorldSpace;
}



void CRole::update(float dt)
{
    CSpriteObject::update(dt);
    updateShootPointInWorldSpace();
    
    if (m_pGun)
    {
        m_pGun->update(dt);
        m_pGun->shoot(dt);
    }

}



void CRole::clearAll()
{
    CSpriteObject::clearAll();
    
    clearThis();
}



void CRole::clearThis()
{
    if (m_pGun)
    {
        m_pGun->clearAll();
        setGun(NULL);
    }
}



bool CRole::createGun(const string& name)
{
    if (NULL != getGun())
    {
        m_pGun->removeFromParentAndCleanup(true);
        m_pGun->clearAll();
        setGun(NULL);
    }
    
    setGun(dynamic_cast<CGun*>(CObjectBase::createObject(name)));
    if (NULL == getGun())
    {
        return false;
    }
    m_pGun->setOwner(this);
    addChild(m_pGun);
    
    return true;
}



bool CRole::attachSpriteTo(CCNode* parent, int zOrder, int tag)
{
    if (!CSpriteObject::attachSpriteTo(parent, zOrder, tag))
    {
        return false;
    }
    
    if (NULL != m_pGun)
    {
        m_pGun->attachBatchNodeToParent(this, zOrder, tag);
    }
    return true;
}



bool CRole::changeBullet(const string& name)
{
    if (NULL == m_pGun)
    {
        return false;
    }
    
    return m_pGun->changeBullet(name);
}



void CRole::updateShootPointInWorldSpace()
{
    CCNode* pSpr = getInnerSprite();
    if (NULL != pSpr && NULL != pSpr->getParent())
    {
        m_shootPointInWorldSpace = pSpr->getParent()->convertToWorldSpace(ccpAdd(getSpritePosition(), m_shootPoint));
    }
}




