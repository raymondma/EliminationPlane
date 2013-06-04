//
//  CVisibleObject.h
//  TheForce
//
//  Created by Ray M on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFVisibleObject__
#define __TheForce__TFVisibleObject__

#include "CObjectBase.h"

class CVisibleObject : public CObjectBase
{
public:
    virtual ~CVisibleObject();
    
    virtual CCRect getSpriteBoundingBox() const;
    virtual CCRect getSpriteBoundingBoxInWorldSpace();
    virtual CCPoint getSpritePosition() const;
    virtual void setSpritePosition(const CCPoint& point);
    virtual void setSpriteVisible(bool visible);
    virtual void setSpriteScaleX(float sx);
    virtual void setSpriteScaleY(float sy);
    virtual void setSpriteScale(float s);
    virtual bool isSpriteVisible();
    virtual CCSize getSpriteContentSize();
    virtual void setSpriteZOrder(int z);
    virtual bool isSpriteInScreen();
    virtual void removeSpriteFromParentAndCleanup(bool cleanup=true);
    virtual bool runSpriteAction(CCAction* action);
    virtual void setSpriteAnchorPoint(const CCPoint& point);
    virtual void stopSpriteAllActions();

    virtual int getCollisionGroup();
    
    virtual bool attachSpriteTo(CCNode* parent, int zOrder=0, int tag=-1);
    
    virtual bool isNeedCheckCollision();
    virtual bool isCollsionWith(TFCollisionProtocol* obj);
    
    virtual void update(float dt);
    
    virtual void turnOffCollision();
    virtual void turnOnCollision();
    
    virtual void die();
    virtual void revive();
    
    virtual void clearAll();
    
    DECLARE_DICTFUNC(int, CollisionGroup);
protected:
    CVisibleObject();
    void clearThis();
    
    virtual void updateBoundingBoxInWorldSpace();
    virtual CCNode* getInnerSprite() const=0;
    
    CCRect m_boundingBoxInWorldSpace;
    bool m_isCacheBoundingBox;
    
    CCArray m_runningActions;
private:
};

#endif /* defined(__TheForce__TFVisibleObject__) */
