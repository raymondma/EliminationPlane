//
//  CObjectBase.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CObjectBase.h"
#include "TFGameObjectManager.h"



DEFINE_DICTFUNC_STR(CObjectBase, CateName);
DEFINE_DICTFUNC_STR(CObjectBase, Name);


CObjectBase* CObjectBase::createObject(const string& name)
{
    CObjectBase* pObject = NULL;
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



CObjectBase::CObjectBase() :
pObjectDictionary_(NULL)
, m_isDead(false)
{
    
}



CObjectBase::~CObjectBase()
{
    clearThis();
}



bool CObjectBase::init(CCDictionary* pObjectDict)
{
//    CCAssert(NULL != pObjectDict, "pObjectDict can't be NULL");
    clearAll();
    revive();
    
    setObjectDictionary(pObjectDict);

    turnOnCollision();
    return true;
}



void CObjectBase::clearAll()
{
    clearThis();
}




void CObjectBase::clearThis()
{
    turnOffCollision();
    setObjectDictionary(NULL);
    removeAllChildrenWithCleanup(true);
    clearState();
}



void CObjectBase::die()
{
    m_isDead = true;
    turnOffCollision();
}



void CObjectBase::revive()
{
    m_isDead = false;
    turnOnCollision();
}



bool CObjectBase::isDead() const
{
    return m_isDead;
}



void CObjectBase::update(float dt)
{
    CCArray* children = getChildren();
    CCObject* pObj;
    CCARRAY_FOREACH(children, pObj)
    {
        pObj->update(dt);
    }
}



int CObjectBase::getLevel()
{
    return 1;
}



bool CObjectBase::isNeedCheckCollision()
{
    return !isDead();
}

