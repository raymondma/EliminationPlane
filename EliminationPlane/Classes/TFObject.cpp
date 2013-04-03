//
//  TFObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFObject.h"
#include "TFGameObjectManager.h"



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

    pObject = OBJECT_FACTORY->createInstance(strCateName->getCString());
    
    if (pObject)
    {
        pObject->init(pDict);
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

