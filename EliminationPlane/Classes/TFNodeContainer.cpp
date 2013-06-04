//
//  TFNodeContainer.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-21.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFNodeContainer.h"
#include "TFTexturesCache.h"
#include "TFBattleFieldLayer.h"
#include "CObjectBase.h"


TFNodeContainer::TFNodeContainer()
{
    
}



TFNodeContainer::~TFNodeContainer()
{
    clear();
}



CObjectBase* TFNodeContainer::checkoutElement()
{
    if (containerUnUseArray_.count() == 0)
    {
        return NULL;
    }
    
    CObjectBase* pObj = static_cast<CObjectBase*>(containerUnUseArray_.lastObject());
    
    containerInUseArray_.addObject(pObj);
    containerUnUseArray_.removeLastObject();
    
//    if (dynamic_cast<TFItemInGame*>(pObj))
//    {
//        CCLOG("checkout: Sprite:0x%X, 0x%X",(void*)pObj, (void*)(pObj->getSprite()));
//    }
    
    return pObj;
}



void TFNodeContainer::checkinElement(CObjectBase* elem)
{
    CC_ASSERT(NULL != elem);
    
    unsigned int idx = containerInUseArray_.indexOfObject(elem);
    if (CC_INVALID_INDEX == idx)
    {
        return;
    }
    
//    if (dynamic_cast<TFItemInGame*>(elem))
//    {
//        CCLOG("checkin: Sprite:0x%X, 0x%X",(void*)elem, (void*)(elem->getSprite()));
//    }

    containerUnUseArray_.addObject(elem);
    containerInUseArray_.removeObjectAtIndex(idx);
}



void TFNodeContainer::clear()
{
    CCObject* pObj;
    CCARRAY_FOREACH(&containerInUseArray_, pObj)
    {
        CObjectBase* pTFObj = dynamic_cast<CObjectBase*>(pObj);
        if (NULL != pTFObj)
        {
            pTFObj->clearAll();
        }
    }
    CCARRAY_FOREACH(&containerUnUseArray_, pObj)
    {
        CObjectBase* pTFObj = dynamic_cast<CObjectBase*>(pObj);
        if (NULL != pTFObj)
        {
            pTFObj->clearAll();
        }
    }
    containerInUseArray_.removeAllObjects();
    containerUnUseArray_.removeAllObjects();
}



bool TFNodeContainer::initCache(const string& name, int num)
{
    for (int i = 0; i < num; ++i)
    {
        CObjectBase* pObj = CObjectBase::createObject(name);
        if (NULL != pObj)
        {
            pObj->die();
            containerUnUseArray_.addObject(pObj);
        }
        else
        {
            __CCLOGWITHFUNCTION("can't create %s", name.c_str());
            return false;
        }
    }
    
    return true;
}



const CCArray* TFNodeContainer::getInUseArray() const
{
    return &containerInUseArray_;
}



unsigned int TFNodeContainer::getInUseCount()
{
    return containerInUseArray_.count();
}




