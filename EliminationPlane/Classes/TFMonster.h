//
//  TFMonster.h
//  TheForce
//
//  Created by 马 俊 on 13-2-4.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFMonster__
#define __TheForce__TFMonster__

#include "TFRole.h"
#include "TFCollisionProtocol.h"
#include "TFHPBar.h"

class TFMonster : public TFRole
{
    friend class TFObject;
    CC_SYNTHESIZE_RETAIN(TFHPBar*, m_pHPBar, HPBar);
public:
    virtual ~TFMonster();
    virtual bool init(CCDictionary* pObjectDict);
    
    virtual void update(float dt);
    virtual void die();
    virtual void revive();
    virtual void clearAll();

    virtual void checkCollision(TFCollisionProtocol* rb);

#ifdef DEBUG
    virtual string whoAmI(){return "Monster";}
#endif
    
    DECLARE_DICTFUNC(float, MaxHP);
protected:
    TFMonster();
    void clearThis();

    virtual void castItems();
    virtual bool createHPBar();
    
    int m_hitPoint;
    int m_maxHitPoint;
    float m_hitTime;
    float m_speed;
private:
};

#endif /* defined(__TheForce__TFMonster__) */
