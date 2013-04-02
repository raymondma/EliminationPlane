//
//  TFBackground.cpp
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//
#include "cocos2d.h"
#include "TFBackground.h"
#include "TFTexturesCache.h"
#include "Common.h"


TFBackground::TFBackground() : pSpriteBatchNode_(NULL), m_speed(1.0f)
{
}



TFBackground::~TFBackground()
{
}



float TFBackground::getSpeed() const
{
    return m_speed;
}



void TFBackground::setSpeed(float s)
{
    m_speed = s;
}



bool TFBackground::init()
{
//    int bgNum = rand() % 5;

    char bgName[] = "background";
//    sprintf(bgName, "bg%d", bgNum);
    
    CCSprite *pSpr = NULL;
	do
	{
		const CCSize& sz = CCDirector::sharedDirector()->getWinSize();
        pSpriteBatchNode_ = TEXTURE_CACHE->createSpriteBatchNode(GA_SCENES);
        this->addChild(pSpriteBatchNode_);
        
        pSpr = CCSprite::createWithSpriteFrameName(bgName);
        CCSize frameSize = pSpr->getContentSize();
        pSpr->setAnchorPoint(CCPointZero);
        pSpr->setPosition(CCPointZero);
        pSpriteBatchNode_->addChild(pSpr);
        
        m_num = (int)(sz.height / frameSize.height) + 2;
        
        for (int i = 1; i < m_num; i++)
        {
            pSpr = CCSprite::createWithSpriteFrameName(bgName);
            pSpr->setAnchorPoint(CCPointZero);
            pSpr->setPosition(ccp(0, (frameSize.height - 1) * i));
            pSpriteBatchNode_->addChild(pSpr);
        }
		
		return true;
	} while (0);
    
    // RAY: The release is not needed.If a CCNode object is not added to a parent,it will be released automatically in next frame.
	CC_SAFE_RELEASE(pSpr);
	return false;
}



void TFBackground::update(float dt)
{
	CCNode::update(dt);
    
	if (FLT_EQUAL(m_speed, 0.f)) return;
	
	CCObject* pObj;
	CCArray* children = pSpriteBatchNode_->getChildren();
	CCARRAY_FOREACH(children, pObj)
	{
		CCSprite* pSpr = dynamic_cast<CCSprite*>(pObj);
        CCSize sz = pSpr->getContentSize();
		CCPoint pos = pSpr->getPosition();
        
		pos.y -= m_speed;
        
        if (pos.y < -sz.height)
        {
            pos.y += (sz.height - 1) * m_num;
        }
        
        pSpr->setPosition(pos);
	}
}


