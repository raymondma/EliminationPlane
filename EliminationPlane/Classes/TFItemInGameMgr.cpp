//
//  TFItemInGameMgr.cpp
//  TheForce
//
//  Created by Ray M on 13-2-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFItemInGameMgr.h"
#include "TFTexturesCache.h"
#include "TFItemInGame.h"
#include "TFGameObjectManager.h"


const char* TFItemInGameMgr::m_sItemNames[INGAME_ITEM_NUM] =
{
    "Coin",
    "Magnet",
};

const int TFItemInGameMgr::m_sItemCacheNum[INGAME_ITEM_NUM] =
{
    1, // Coin
    1,  // Magnet
};



TFItemInGameMgr::TFItemInGameMgr() :
pContainers_(NULL)
{
}



TFItemInGameMgr::~TFItemInGameMgr()
{
    clearAll();
}



void TFItemInGameMgr::clearAll()
{
    if (NULL != pContainers_)
    {
        for (int i=0; i<INGAME_ITEM_NUM; ++i)
        {
            pContainers_[i].clear();
        }
    }
    CC_SAFE_DELETE_ARRAY(pContainers_);
}



bool TFItemInGameMgr::init()
{
    clearAll();
    
    pContainers_ = new TFNodeContainer[INGAME_ITEM_NUM];
    
    for (int i=0; i<INGAME_ITEM_NUM; ++i )
    {
        if (!pContainers_[i].initCache(m_sItemNames[i], m_sItemCacheNum[i]))
        {
            return false;
        }
    }

    
    if (!TFBatchNodeObject::init())
    {
        return false;
    }

    return true;
}



bool TFItemInGameMgr::createNewItem(INGAME_ITEM_TYPE type, const CCPoint& pt)
{
    TFItemInGame* pItem = dynamic_cast<TFItemInGame*>(pContainers_[type].checkoutElement());
    if (NULL == pItem)
    {
        return false;
    }
    
    pItem->revive();
    pItem->attachSpriteTo(getBatchNode()->getParent());
    pItem->setSpritePosition(pt);
    
    CCPoint cp1 = getControlPoint1(pt);
    CCPoint cp2 = getControlPoint2(pt, cp1);
    CCPoint ep = getEndPoint(cp2);
    
    ccBezierConfig bc;
    bc.controlPoint_1.x = cp1.x;
    bc.controlPoint_1.y = cp1.y;
    bc.controlPoint_2.x = cp2.x;
    bc.controlPoint_2.y = cp2.y;
    bc.endPosition.x = ep.x;
    bc.endPosition.y = ep.y;
    
    CCBezierTo* pAction = CCBezierTo::create(2.f, bc);
    pAction->setTag(997);
    pItem->runSpriteAction(pAction);

    return true;
}



void TFItemInGameMgr::update(float dt)
{
    CCObject* pObj;
    
    for (int i=0; i<INGAME_ITEM_NUM; ++i)
    {
        CCArray needToCheckIn;
        const CCArray* children = pContainers_[i].getInUseArray();
        CCARRAY_FOREACH(children, pObj)
        {
            TFItemInGame* pSpr = dynamic_cast<TFItemInGame*>(pObj);
            if (pSpr)
            {
                pSpr->update(dt);
                if (pSpr->isDead())
                {
                    pSpr->removeSpriteFromParentAndCleanup(false);
                    needToCheckIn.addObject(pSpr);
                }
            }
        }
        CCARRAY_FOREACH(&needToCheckIn, pObj)
        {
            pContainers_[i].checkinElement(static_cast<TFItemInGame*>(pObj));
        }
        needToCheckIn.removeAllObjects();
    }
}


CCPoint TFItemInGameMgr::getControlPoint1(const CCPoint& firstPoint)
{
    const int W = 80;
    const int H = 50;

    CCPoint pt = firstPoint;

    if (pt.x - W
        > 0)
    {
        pt.x = pt.x-W;
    }
    
    pt.x = pt.x + rand() % W;
    pt.y = 60 + pt.y + H + rand() % H;
    
    return pt;
}



CCPoint TFItemInGameMgr::getControlPoint2(const CCPoint& firstPoint, const CCPoint& cp1)
{
    const int H = 40;
    
    CCPoint pt = firstPoint;

    pt.x = cp1.x;
    pt.y -= rand() % H;
    
    if (pt.y < 0)
    {
        pt.y = 0;
    }
    
    return pt;
}



CCPoint TFItemInGameMgr::getEndPoint(const CCPoint& cp2)
{
    return ccp(cp2.x, -60);
}



GameArts TFItemInGameMgr::getBatchNodeName()
{
    return GA_ACTORS;
}
