//
//  TFRole.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//
#include "TFRole.h"
#include "TFBulletBase.h"
#include "TFGameObjectManager.h"


DEFINE_DICTFUNC_DICTIONARY(TFRole, Gun);




TFRole::TFRole() : m_pGun(NULL)
{

}



TFRole::~TFRole()
{
    clearThis();
}



bool TFRole::init(CCDictionary* pObjectDict)
{
    if (!TFSpriteObject::init(pObjectDict))
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



CCPoint TFRole::getShootPoint()
{
//    return ccpAdd(getSpritePosition(), m_shootPoint);
    return m_shootPointInWorldSpace;
}



void TFRole::update(float dt)
{
    TFSpriteObject::update(dt);
    updateShootPointInWorldSpace();
    
    if (m_pGun)
    {
        m_pGun->update(dt);
        m_pGun->shoot(dt);
    }

}



void TFRole::clearAll()
{
    TFSpriteObject::clearAll();
    
    clearThis();
}



void TFRole::clearThis()
{
    if (m_pGun)
    {
        m_pGun->clearAll();
        setGun(NULL);
    }
}



bool TFRole::createGun(const string& name)
{
    if (NULL != getGun())
    {
        m_pGun->removeFromParentAndCleanup(true);
        m_pGun->clearAll();
        setGun(NULL);
    }
    
    setGun(dynamic_cast<TFGun*>(TFObject::createObject(name)));
    if (NULL == getGun())
    {
        return false;
    }
    m_pGun->setOwner(this);
    addChild(m_pGun);
    
    return true;
}



bool TFRole::attachSpriteTo(CCNode* parent, int zOrder, int tag)
{
    if (!TFSpriteObject::attachSpriteTo(parent, zOrder, tag))
    {
        return false;
    }
    
    if (NULL != m_pGun)
    {
        m_pGun->attachBatchNodeToParent(this, zOrder, tag);
    }
    return true;
}



bool TFRole::changeBullet(const string& name)
{
    if (NULL == m_pGun)
    {
        return false;
    }
    
    return m_pGun->changeBullet(name);
}



void TFRole::updateShootPointInWorldSpace()
{
    CCNode* pSpr = getInnerSprite();
    if (NULL != pSpr && NULL != pSpr->getParent())
    {
        m_shootPointInWorldSpace = pSpr->getParent()->convertToWorldSpace(ccpAdd(getSpritePosition(), m_shootPoint));
    }
}




