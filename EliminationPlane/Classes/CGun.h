//
//  CGun.h
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFGun__
#define __TheForce__TFGun__
#include "cocos2d.h"

#include <vector>
#include <string>

#include "TFNodeContainer.h"
#include "CObjectBase.h"
#include "TFBatchNodeObject.h"


using namespace std;
USING_NS_CC;

class CRole;
class CBulletBase;

class CGun : public CObjectBase, public TFBatchNodeObject
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(CGun);
    virtual ~CGun();
    virtual bool init(CCDictionary* pObjectDict);
    
    virtual void setOwner(CRole* role);
    virtual void update(float dt);
    virtual void shoot(float dt);
    virtual void clearAll();

    virtual bool addBulletRow();
    virtual bool removeBulletRow();
    
    virtual bool changeBullet(const string& name);
    
    DECLARE_DICTFUNC(CCString*, BulletName);
    DECLARE_DICTFUNC(int, MaxLevel);
    DECLARE_DICTFUNC(int, CacheNum);
    DECLARE_DICTFUNC(float, Frequency);
protected:
    CGun();
    void clearThis();
    virtual GameArts getBatchNodeName();
    
    CRole* m_pRole;

    float m_lastShootTime;
    float m_frequency;
    bool m_isDoubleBullet;

private:
    TFNodeContainer container_;
};


#endif /* defined(__TheForce__TFGun__) */
