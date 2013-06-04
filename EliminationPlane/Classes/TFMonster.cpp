//
//  TFMonster.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-4.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFMonster.h"
#include "CBulletBase.h"
#include "TFHPBar.h"
#include "TFBattleFieldLayer.h"

#include "TFItemInGameMgr.h"
#include "TFBattleFieldDataMgr.h"

#include "TFPathManager.h"
#include "TFPath.h"


DEFINE_DICTFUNC(TFMonster, float, MaxHP, 0);


TFMonster::TFMonster() : m_pHPBar(NULL)
,m_speed(180)
,path_(NULL)
,splineIdx_(0)
{
    
}



TFMonster::~TFMonster()
{
    clearThis();
}



void TFMonster::clearAll()
{
    CRole::clearAll();
    clearThis();
}



void TFMonster::clearThis()
{
    if (getHPBar())
    {
        getHPBar()->clearAll();
        setHPBar(NULL);
    }
}



void TFMonster::checkCollision(TFCollisionProtocol* rb)
{
    CBulletBase* pB = dynamic_cast<CBulletBase*>(rb);
    if (pB)     // Hit Bullet, Dead!
    {
        m_hitPoint -= pB->getDamage();

        if (m_hitPoint <= 0)
        {
            if (m_pHPBar)
            {
                m_pHPBar->setPercentage(0.f);
            }
            changeState(string("Dead"));
            die();
            castItems();
        }
        else
        {
            if (m_pHPBar)
            {
                m_pHPBar->setSpriteVisible(true);
                m_pHPBar->setPercentage((float)m_hitPoint / (float)m_maxHitPoint);
            }
            
            changeState("Damage");
            m_hitTime = 0.f;
        }
    }
}


bool TFMonster::init(CCDictionary* pObjectDict)
{
    if (!CRole::init(pObjectDict))
    {
        return false;
    }
    
    m_maxHitPoint = getMaxHPFromDict();
    m_hitPoint = m_maxHitPoint;
    
//    if (!createHPBar())
//    {
//        return false;
//    }
//    
//    m_pHPBar->setPercentage(1.f);
//    m_pHPBar->setSpriteVisible(false);

    path_ = PATH_MANAGER->getPath();
    return true;
}



void TFMonster::update(float dt)
{    
    CRole::update(dt);

    static float time = 0;
    if (!isDead())
    {
//        float offset = m_speed * dt;
//        CCPoint pt = getSpritePosition();
//        pt.y -= offset;
//        
//        setSpritePosition(pt);

//        if (pt.y < -50)
//        {
//            die();
//        }
        const float INTV = 0.01f;
        time += dt;
        if (time >= INTV)
        {
            time -= INTV;
            if (path_)
            {
                CCArray* spline = path_->getSpline();
                CCPoint* pt = dynamic_cast<CCPoint*>(spline->objectAtIndex(splineIdx_));
                setSpritePosition(*pt);
                splineIdx_++;
                
                if (splineIdx_ >= spline->count())
                {
                    splineIdx_ = 0;
                }
            }
        }

    }
    
    if (this->getCurrentState() == "Damage")
    {
        m_hitTime += dt;
        if (m_hitTime >= 0.1)
        {
            changeState("Fly");
            m_hitTime = 0;
        }
    }


    return;
}



void TFMonster::die()
{
    CRole::die();

    if (m_pHPBar != NULL)
    {
        m_pHPBar->setSpriteVisible(false);
    }
}



void TFMonster::revive()
{
    CRole::revive();
    m_hitPoint = m_maxHitPoint;
}



void TFMonster::castItems()
{
    int data = rand() % 100;
    
    
//    if (data < 7)
//    {
//        ITEM_IN_GAME_MANAGER->createNewItem(string("ItemInvincible"), getSpritePosition());
//    }
//    else if (data < 15)
    if (data < 15)
    {
        ITEM_IN_GAME_MANAGER->createNewItem(INGAME_ITEM_MAGNET, getSpritePosition());
    }
    else
    {
        ITEM_IN_GAME_MANAGER->createNewItem(INGAME_ITEM_COIN, getSpritePosition());
    }
}



bool TFMonster::createHPBar()
{
    setHPBar(dynamic_cast<TFHPBar*>(CObjectBase::createObject("MonsterHPBar")));
    if (NULL == getHPBar())
    {
        return false;
    }

    float w = m_pHPBar->getSpriteContentSize().width;
    m_pHPBar->setSpritePosition(ccp(w / 2.f + 2.f, 0));
    addChild(m_pHPBar);
    m_pHPBar->attachSpriteTo(getInnerSprite());
    
    return true;
}
