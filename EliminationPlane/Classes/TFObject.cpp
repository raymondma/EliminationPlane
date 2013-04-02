//
//  TFObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFObject.h"
#include "TFGameObjectManager.h"
#include "TFRole.h"
#include "TFBulletBase.h"
#include "TFMonster.h"
#include "TFItemInGame.h"
#include "TFHPBar.h"
#include "TFGun.h"


DEFINE_DICTFUNC_STR(TFObject, CateName);
DEFINE_DICTFUNC_STR(TFObject, Name);


TFObject* TFObject::createObject(const string& name)
{
    TFObject* pObject = NULL;
    CCDictionary* pDict = GAME_OJBECT_MANAGER->getObjectByName(name);
    if (!pDict)
    {
        return NULL;
    }
    
    CCString* strCateName = dynamic_cast<CCString*>(pDict->objectForKey("CateName"));
    if (NULL == strCateName)
    {
        return NULL;
    }

    pObject = createObjectByClassName(strCateName->getCString());
    
    if (pObject)
    {
        pObject->init(pDict);
    }
    return pObject;
}



TFObject* TFObject::createObjectByClassName(const string& className)
{
    TFObject* pObject = NULL;
    
    if (className.compare("TFRole") == 0)
    {
        pObject = new TFRole;
    }
    else if (className.compare("TFBulletBase") == 0)
    {
        pObject = new TFBulletBase;
    }
    else if (className.compare("TFMonster") == 0)
    {
        pObject = new TFMonster;
    }
    else if (className.compare("TFItemInGame") == 0)
    {
        pObject = new TFItemInGame;
    }
    else if (className.compare("TFHPBar") == 0)
    {
        pObject = new TFHPBar;
    }
    else if (className.compare("TFGun") == 0)
    {
        pObject = new TFGun;
    }
    else if (className.compare("TFScale9SpriteObject") == 0)
    {
        pObject = new TFScale9SpriteObject;
    }

#ifdef DEBUG
    else
    {
        __CCLOGWITHFUNCTION("create role object failed: %s", className.c_str());
        return NULL;
    }
#endif

    if (pObject)
    {
        pObject->autorelease();
    }
    return pObject;
}




TFObject::TFObject() :
pObjectDictionary_(NULL)
, m_isDead(false)
{
    
}



TFObject::~TFObject()
{
    clearThis();
}



bool TFObject::init(CCDictionary* pObjectDict)
{
//    CCAssert(NULL != pObjectDict, "pObjectDict can't be NULL");
    clearAll();
    revive();
    
    setObjectDictionary(pObjectDict);

    turnOnCollision();
    return true;
}



void TFObject::clearAll()
{
    clearThis();
}




void TFObject::clearThis()
{
    turnOffCollision();
    setObjectDictionary(NULL);
    removeAllChildrenWithCleanup(true);
    clearState();
}



void TFObject::die()
{
    m_isDead = true;
    turnOffCollision();
}



void TFObject::revive()
{
    m_isDead = false;
    turnOnCollision();
}



bool TFObject::isDead() const
{
    return m_isDead;
}



void TFObject::update(float dt)
{
    CCArray* children = getChildren();
    CCObject* pObj;
    CCARRAY_FOREACH(children, pObj)
    {
        pObj->update(dt);
    }
}



int TFObject::getLevel()
{
    return 1;
}



bool TFObject::isNeedCheckCollision()
{
    return !isDead();
}

