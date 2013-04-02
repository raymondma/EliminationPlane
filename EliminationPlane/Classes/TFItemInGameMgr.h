//
//  TFItemInGameMgr.h
//  TheForce
//
//  Created by Ray M on 13-2-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFItemInGameMgr__
#define __TheForce__TFItemInGameMgr__

#include "cocos2d.h"
#include <string>

#include "TFNodeContainer.h"
#include "TFBatchNodeObject.h"

USING_NS_CC;
using namespace std;

class TFItemInGame;


enum INGAME_ITEM_TYPE
{
    INGAME_ITEM_COIN,
    INGAME_ITEM_MAGNET,
    
    INGAME_ITEM_NUM,
};


class TFItemInGameMgr : public TFBatchNodeObject
{
public:
    TFItemInGameMgr();
    ~TFItemInGameMgr();

    bool init();
    bool createNewItem(INGAME_ITEM_TYPE type, const CCPoint& pt);
    void update(float dt);
    
    void clearAll();
    
protected:
    
    
    virtual GameArts getBatchNodeName();
    
    TFItemInGame* GetItemFromCache();
    CCPoint getControlPoint1(const CCPoint& firstPoint);
    CCPoint getControlPoint2(const CCPoint& firstPoint, const CCPoint& cp1);
    CCPoint getEndPoint(const CCPoint& cp2);

    static const char* m_sItemNames[INGAME_ITEM_NUM];
    static const int m_sItemCacheNum[INGAME_ITEM_NUM];
private:
    TFNodeContainer* pContainers_;
};


#endif /* defined(__TheForce__TFItemInGameMgr__) */
