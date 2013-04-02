//
//  TFBattleFieldLayer.cpp
//  TheForce
//
//  Created by Ming Zhao on 2/1/13.
//  Copyright Tencent 2013. All rights reserved.
//
#include "Common.h"

#include "TFBattleFieldLayer.h"
//#include "SimpleAudioEngine.h"
#include "TFGameObjectManager.h"
#include "TFBattleFieldDataMgr.h"
#include "TFCollisionMgr.h"
#include "TFItemInGameMgr.h"


TFBattleFieldLayer* TFBattleFieldLayer::spInstance_ = NULL;

TFBattleFieldLayer* TFBattleFieldLayer::getInstance()
{
    if (!spInstance_)
    {
        spInstance_ = new TFBattleFieldLayer;
        spInstance_->autorelease();
    }
    return spInstance_;

}



TFBattleFieldLayer::TFBattleFieldLayer() :
pBkg_(NULL)
,pItemInGameMgr_(NULL)
,pBattleField_(NULL)
,m_isGameOver(false)
{
}



TFBattleFieldLayer::~TFBattleFieldLayer()
{
    removeAllListener();

    CC_SAFE_DELETE(pItemInGameMgr_);
    CC_SAFE_DELETE(pBattleField_);
    setBkg(NULL);
    
    delete COLLISION_MANAGER;
    
    spInstance_ = NULL;
}



TFItemInGameMgr* TFBattleFieldLayer::getItemInGameMgr()
{
    return pItemInGameMgr_;
}



bool TFBattleFieldLayer::init()
{
    COLLISION_MANAGER->clearAll();
    
    spInstance_ = this;
    m_isGameOver = false;
    
    setTouchEnabled(true);
    
    initListener();
    
    loadConfig();
    
    pBattleField_ = new TFBattleFieldDataMgr;
    pItemInGameMgr_ = new TFItemInGameMgr;
    
    setBkg(TFBackground::create());
    addChild(getBkg(), -100);
    
//    m_timeLabel = CCLabelTTF::create("the string", "Marker Felt", 21);
//    m_timeLabel->setPosition(ccp(100, 450));
//    addChild(m_timeLabel, 1000);
    
//    if (pBattleField_->init())
//    {
//        // TODO: get param values from configuration file
//        if (!pBattleField_->setBattleFieldDataByName(string("SceneDemo")))
//        {
//            return false;
//        }
//        // TODO: speicify zorder and tag if need
//        addChild(pBattleField_, 200);
//        pBattleField_->attachBatchNodeToParent(this, 100);
//    }
//    else
//    {
//        return false;
//    }
    
//    if (pItemInGameMgr_->init())
//    {
//        // TODO: speicify zorder and tag if need
//        pItemInGameMgr_->attachBatchNodeToParent(this, 0);
//    }
//    else
//    {
//        return false;
//    }

	
    // TODO: get the param values from configuration file.
    
    scheduleUpdate();
 
    return true;
}



void TFBattleFieldLayer::update(float dt)
{
    if (m_isGameOver)
    {
        return;
    }
    
    pBkg_->update(dt);
//    pItemInGameMgr_->update(dt);
//    pBattleField_->update(dt);
    COLLISION_MANAGER->update();

}



//void TFBattleFieldLayer::registerWithTouchDispatcher()
//{
//	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
//}



void TFBattleFieldLayer::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent)
{
    if (m_isGameOver)
    {
        return;
    }
    
	if (pTouches->count() > 0)
	{
        wipeY_ = 0.f;
	}
}



void TFBattleFieldLayer::ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent)
{
    if (m_isGameOver)
    {
        return;
    }
	
    if (pTouches->count() > 0)
	{
		CCTouch *pTouch =(CCTouch*)* pTouches->begin();
		CCPoint Delta = pTouch->getDelta();

        wipeY_ += Delta.y;
        
//        m_pHero->MoveDelta(Delta.x);
	}
}



void TFBattleFieldLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{

}



void TFBattleFieldLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
//    if (wipeY_ >= 120)
//    {
//        m_pHero->triggerSkill();
//    }
}



void TFBattleFieldLayer::initListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TFBattleFieldLayer::onGameOver), NOTIFICATION_HERO_DEAD, NULL);
}



void TFBattleFieldLayer::removeAllListener()
{
//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFICATION_HERO_DEAD);
}



void TFBattleFieldLayer::onGameOver(CCObject* obj)
{
    pBkg_->setSpeed(0.f);
    m_isGameOver = true;
    removeAllListener();
}



bool TFBattleFieldLayer::loadConfig()
{
    return true;
}

