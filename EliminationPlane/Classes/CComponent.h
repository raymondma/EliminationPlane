//
//  CComponent.h
//  GingyBattle
//
//  Created by 马 俊 on 13-4-23.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __GingyBattle__GBComponent__
#define __GingyBattle__GBComponent__
#include "cocos2d.h"
#include "CObjectBase.h"
#include "CComponentParameter.h"

USING_NS_CC;


class CComponent : public CCObject
{
    CC_SYNTHESIZE_RETAIN(CObjectBase*, m_pTarget, Target);
public:
    virtual void update(float dt) = 0;
    virtual void setParameter(CComponentParameter* parameter) = 0;

    virtual void onEnterComponent();
    virtual void onLeaveComponent();
protected:
    CComponent();
    virtual ~CComponent();

private:
};

#endif /* defined(__GingyBattle__GBComponent__) */
