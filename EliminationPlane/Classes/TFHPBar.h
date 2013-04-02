//
//  TFHPBar.h
//  TheForce
//
//  Created by Ray M on 13-2-19.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFHPBar__
#define __TheForce__TFHPBar__

#include "TFSpriteObject.h"
#include "TFScale9SpriteObject.h"


class TFHPBar : public TFSpriteObject
{
    friend class TFObject;
    CC_SYNTHESIZE_RETAIN(TFScale9SpriteObject*, m_pBar, Bar);
public:
    virtual ~TFHPBar();

    virtual void setPercentage(float percentage);
    virtual void setSpriteVisible(bool visible);
    virtual bool init(CCDictionary* pObjectDict);
    virtual void update(float dt);
    virtual void clearAll();
    
    DECLARE_DICTFUNC(CCString*, BarFileName);
protected:
    TFHPBar();
    void clearThis();
    
    void updateBar();

    float m_percentage;
private:
    CCSize OrigBarSize_;
    
};

#endif /* defined(__TheForce__TFHPBar__) */
