//
//  TFBattleFieldLayer.h
//  TheForce
//
//  Created by Ming Zhao on 2/1/13.
//  Copyright Tencent 2013. All rights reserved.
//
#ifndef __TheForce__TFBattleFieldLayer__
#define __TheForce__TFBattleFieldLayer__

#include "TFBackground.h"
#include "TFBattleFieldDataMgr.h"
#include "TFItemInGameMgr.h"


USING_NS_CC;
using namespace std;

class TFBattleFieldLayer : public CCLayer
{
    CC_SYNTHESIZE_RETAIN(TFBackground*, pBkg_, Bkg);
public:
    static TFBattleFieldLayer* getInstance();
    
    virtual bool init();
    void update(float dt);

    
//	void registerWithTouchDispatcher();
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	
    TFItemInGameMgr* getItemInGameMgr();
protected:
    TFBattleFieldLayer();
    ~TFBattleFieldLayer();
    void initListener();
    void removeAllListener();
    void onGameOver(CCObject* obj);

    bool loadConfig();

private:
    static TFBattleFieldLayer* spInstance_;
    TFItemInGameMgr* pItemInGameMgr_;
    TFBattleFieldDataMgr* pBattleField_;

    float wipeY_;
    bool m_isGameOver;
};

#define BATTLE_FIELD_LAYER (TFBattleFieldLayer::getInstance())
#define ITEM_IN_GAME_MANAGER (TFBattleFieldLayer::getInstance()->getItemInGameMgr())

#endif // /* defined(__TheForce__TFBattleFieldLayer__) */
