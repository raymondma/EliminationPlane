//
//  TFBattleFieldDataMgr.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-1.
//  Copyright (c) 2013年 com.tencent. All rights reserved.
//

#include "TFBattleFieldDataMgr.h"
#include "TFMonster.h"
#include "TFTexturesCache.h"
#include "TFGameObjectManager.h"
#include "TFBattleFieldLayer.h"

#include <memory>

using namespace std;

const char* TFBattleFieldDataMgr::m_sMonsterNames[MONSTER_TYPE_NUM] =
{
    "Monster0",
    "Monster1",
    "Monster2",
};


const int TFBattleFieldDataMgr::m_sMonsterCacheNum[MONSTER_TYPE_NUM] =
{
    1,     // for Monster0
    1,     // for Monster1
    1,     // for Monster2
};


TFBattleFieldDataMgr::TFBattleFieldDataMgr() :
pBattleFieldData_(NULL)
,m_gameTime(0.f)
,pContainers_(NULL)
{
    
}



TFBattleFieldDataMgr::~TFBattleFieldDataMgr()
{
    clearThis();
}



void TFBattleFieldDataMgr::clearAll()
{
    CObjectBase::clearAll();
    
    clearThis();
}



void TFBattleFieldDataMgr::clearThis()
{
    clearBattleFieldData();
    removeAllListener();

    
    if (NULL != pContainers_)
    {
        for (int i=0; i<INGAME_ITEM_NUM; ++i)
        {
            pContainers_[i].clear();
        }
    }
    CC_SAFE_DELETE_ARRAY(pContainers_);
    
    m_monsterTypeNameTable.clear();
    
    TFBatchNodeObject::clearAllBatchNode();
}



bool TFBattleFieldDataMgr::init()
{
    clearAll();
    
	const char* st = "BattleFieldTable.plist";
	const char* fst = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(st);
	if (!initBattleFieldData(fst))
    {
        return false;
    }

    pContainers_ = new TFNodeContainer[MONSTER_TYPE_NUM];
    for (int i=0; i<MONSTER_TYPE_NUM; ++i)
    {
        m_monsterTypeNameTable[string(m_sMonsterNames[i])] = i;
        if (!pContainers_[i].initCache(m_sMonsterNames[i], m_sMonsterCacheNum[i]))
        {
            return false;
        }
    }
    
    if (!TFBatchNodeObject::init())
    {
        return false;
    }
    
    initListener();

    return true;
}



bool TFBattleFieldDataMgr::initBattleFieldData(const char* fn)
{
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(fn);
	CCArray* aKeys = dict->allKeys();
	if(aKeys->count() == 0)
    {
        return false;
    }
	CCObject* pObj;
	CCARRAY_FOREACH(aKeys, pObj)
	{
		CCString* strKey = (CCString*)pObj;
        auto_ptr<TFBattleFieldData> pBattleFieldData(new TFBattleFieldData);
        pBattleFieldData->m_Name = strKey->getCString();
        CCDictionary* pBattleFieldDict = (CCDictionary*)dict->objectForKey(pBattleFieldData->m_Name);
        CCString* s;

        s = (CCString*)pBattleFieldDict->objectForKey(string("StartPosX"));
        if (NULL == s)
        {
            return false;
        }
        pBattleFieldData->m_StartPosX = s->floatValue();
        
        s = (CCString*)pBattleFieldDict->objectForKey(string("StartPosY"));
        if (NULL == s)
        {
            return false;
        }
        pBattleFieldData->m_StartPosY = s->floatValue();
        
        CCArray* pMonDict = (CCArray*)pBattleFieldDict->objectForKey(string("Monsters"));
        CCARRAY_FOREACH(pMonDict, pObj)
        {
            CCDictionary* pMonsterItemDict = (CCDictionary*)pObj;
            auto_ptr<TFMonsterData> pMonsterData(new TFMonsterData);
            
            s = (CCString*)pMonsterItemDict->objectForKey(string("ComingTime"));
            if (NULL == s)
            {
                return false;
            }
            pMonsterData->Pos = s->floatValue();
            
            s = (CCString*)pMonsterItemDict->objectForKey(string("1"));
            if (NULL == s)
            {
                return false;
            }
            pMonsterData->MonsterLine[0] = s->getCString();
            
            s = (CCString*)pMonsterItemDict->objectForKey(string("2"));
            if (NULL == s)
            {
                return false;
            }
            pMonsterData->MonsterLine[1] = s->getCString();
            
            s = (CCString*)pMonsterItemDict->objectForKey(string("3"));
            if (NULL == s)
            {
                return false;
            }
            pMonsterData->MonsterLine[2] = s->getCString();
            
            s = (CCString*)pMonsterItemDict->objectForKey(string("4"));
            if (NULL == s)
            {
                return false;
            }
            pMonsterData->MonsterLine[3] = s->getCString();
            
            s = (CCString*)pMonsterItemDict->objectForKey(string("5"));
            if (NULL == s)
            {
                return false;
            }
            pMonsterData->MonsterLine[4] = s->getCString();
            
            pBattleFieldData->m_Monsters.push_back(pMonsterData.release());
        }
        
        TFBattleFieldData* pSD = pBattleFieldData.release();
        this->m_battleFieldDatas[pSD->m_Name] = pSD;
    }
    return true;
}



void TFBattleFieldDataMgr::clearBattleFieldData()
{
    for (VSD_IT it = m_battleFieldDatas.begin();
         it!=m_battleFieldDatas.end(); ++it)
    {
        CC_SAFE_DELETE((*it).second);
    }
    m_battleFieldDatas.clear();
}



bool TFBattleFieldDataMgr::setBattleFieldDataByName(const string& name)
{
    VSD_IT it = m_battleFieldDatas.find(name);
    if (it == m_battleFieldDatas.end())
    {
        return false;
    }
    
    pBattleFieldData_ = (*it).second;
    m_curMonsterIt = pBattleFieldData_->m_Monsters.begin();
    
    return true;
}


bool TFBattleFieldDataMgr::createNearbyMonsters()
{
    //    const float MAX_MONSTER_LEN = 1000.f;
    if (NULL == pBattleFieldData_)
    {
        return false;
    }

    TFBattleFieldData::VM& monster = pBattleFieldData_->m_Monsters;
    while ( m_curMonsterIt != monster.end())
    {
        const CCSize& winSz = CCDirector::sharedDirector()->getWinSize();
        
        TFMonsterData* pMD = static_cast<TFMonsterData*>(*m_curMonsterIt);
        if (pMD->Pos <= m_gameTime)
        {
            for (int i=0; i<MAX_MONSTER_IN_A_LINE; ++i)
            {
                const string& ms = pMD->MonsterLine[i];
                if (!ms.empty())
                {
                    MSI_IT it = m_monsterTypeNameTable.find(ms);
                    if (it == m_monsterTypeNameTable.end())
                    {
                        return false;
                    }
                    int type = (*it).second;
                    TFMonster* pMonsterRole = dynamic_cast<TFMonster*>(pContainers_[type].checkoutElement());
                    if (pMonsterRole == NULL)
                    {
                        return false;
                    }
                    
                    pMonsterRole->revive();
                    pMonsterRole->setSpritePosition(ccp(TFMonsterData::MonsterPosInLine[i], winSz.height));

                    pMonsterRole->attachSpriteTo(getBatchNode());
                    addChild(pMonsterRole);
                }
            }
            m_curMonsterIt++;
        }


        break;
    }
    
    
    return true;
}




void TFBattleFieldDataMgr::update(float dt)
{
    CObjectBase::update(dt);
    
    m_gameTime += dt;
    
    createNearbyMonsters();
    
    CCObject* pObj;
    CCArray needToCheckIn;
    
    for (int i=0; i<MONSTER_TYPE_NUM; ++i)
    {
        const CCArray* children = pContainers_[i].getInUseArray();
        CCARRAY_FOREACH(children, pObj)
        {
            TFMonster* pSpr = dynamic_cast<TFMonster*>(pObj);
            if (pSpr)
            {
                if (pSpr->isDead())
                {
                    pSpr->removeSpriteFromParentAndCleanup(false);
                    pSpr->removeFromParentAndCleanup(false);
                    needToCheckIn.addObject(pSpr);
                }
            }
        }
        
        CCARRAY_FOREACH(&needToCheckIn, pObj)
        {
            pContainers_[i].checkinElement(static_cast<TFMonster*>(pObj));
        }
        needToCheckIn.removeAllObjects();
    }
}



float TFBattleFieldDataMgr::getTime()
{
    return m_gameTime;
}



GameArts TFBattleFieldDataMgr::getBatchNodeName()
{
    return GA_ACTORS;
}



void TFBattleFieldDataMgr::initListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TFBattleFieldDataMgr::onHeroNotMove), NOTIFICATION_HERO_IDLE, NULL);
}



void TFBattleFieldDataMgr::removeAllListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFICATION_HERO_IDLE);
}





