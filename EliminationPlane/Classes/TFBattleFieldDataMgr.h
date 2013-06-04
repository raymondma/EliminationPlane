//
//  TFBattleFieldDataMgr.h
//  TheForce
//
//  Created by 马 俊 on 13-2-1.
//  Copyright (c) 2013年 com.tencent. All rights reserved.
//

#ifndef __TheForce__TFBattleFieldDataMgr__
#define __TheForce__TFBattleFieldDataMgr__

#include "cocos2d.h"
#include <string>
#include <vector>

#include "TFBattleFieldData.h"

#include "TFBatchNodeObject.h"
#include "TFNodeContainer.h"


using namespace std;
USING_NS_CC;

enum MONSTER_TYPE
{
    MONSTER_0,
    MONSTER_1,
    MONSTER_2,
    
    MONSTER_TYPE_NUM,
};


class TFHero;

class TFBattleFieldDataMgr : public CObjectBase, public TFBatchNodeObject
{
public:
    TFBattleFieldDataMgr();
    virtual ~TFBattleFieldDataMgr();
    
    virtual void clearAll();
    
    typedef map<string ,TFBattleFieldData*> VSD;
    typedef map<string ,TFBattleFieldData*>::iterator VSD_IT;
    typedef map<string ,TFBattleFieldData*>::const_iterator VSD_CIT;

    bool init();
    void clearBattleFieldData();
    bool setBattleFieldDataByName(const string& name);
    void update(float dt);
    void gameOver();
    float getTime();
    
protected:
    void clearThis();
    bool initBattleFieldData(const char* fn);
    bool createNearbyMonsters();
 
    void initListener();
    void removeAllListener();

    virtual GameArts getBatchNodeName();
    
    float m_gameTime;       // 游戏开始经过的时间，怪物出生依赖它
    VSD m_battleFieldDatas;
    TFBattleFieldData::VM_CIT m_curMonsterIt;
    
    static const char* m_sMonsterNames[MONSTER_TYPE_NUM];
    static const int m_sMonsterCacheNum[MONSTER_TYPE_NUM];
    
    typedef map<string, int> MSI;
    typedef map<string, int>::iterator MSI_IT;
    typedef map<string, int>::const_iterator MSI_CIT;
    MSI m_monsterTypeNameTable;
private:
    TFBattleFieldData* pBattleFieldData_;
    TFNodeContainer* pContainers_;
};


#endif /* defined(__TheForce__TFBattleFieldDataMgr__) */
