//
//  TFBackground.h
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#ifndef __TheForce__TFBackground__
#define __TheForce__TFBackground__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class TFBackground : public CCNode
{
public:
    CREATE_FUNC(TFBackground);
	virtual ~TFBackground();
	
	virtual float getSpeed() const;
	virtual void setSpeed(float s);
    virtual void update(float dt);
    
protected:
	float m_speed;
    int m_num;
    
    TFBackground();
    virtual bool init();
    
private:
    CCSpriteBatchNode *pSpriteBatchNode_;
};

#endif /* defined(__TheForce__TFBackground__) */
