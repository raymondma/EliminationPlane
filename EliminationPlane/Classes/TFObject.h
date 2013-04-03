//
//  TFObject.h
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFObject__
#define __TheForce__TFObject__

#include "cocos2d.h"
#include "cocos-ext.h"

#include <string>

#include "TFObjectFactory.h"
#include "TFStateBase.h"
#include "TFCollisionProtocol.h"

#include "TFPListReaderHelper.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class TFRoleData;

class TFObject : public CCNode, public TFStateBase, public TFCollisionProtocol
{
    CC_SYNTHESIZE_RETAIN(CCDictionary*, pObjectDictionary_, ObjectDictionary);
public:
    // Param: name      the name in GameObject.plist
    static TFObject* createObject(const string& name);

	virtual ~TFObject();
	
    //
	virtual bool init(CCDictionary* pObjectDict);
	virtual void update(float dt);

    virtual void die();
    virtual void revive();
    virtual bool isDead() const;
    
    virtual void clearAll();
    
    virtual bool isNeedCheckCollision();
    
    // functions for read data from pObjectDictionary_
    DECLARE_DICTFUNC(CCString*, CateName);
    DECLARE_DICTFUNC(CCString*, Name);
    
    ////////////////////
    virtual int getLevel();
    
    
#ifdef DEBUG
    virtual string whoAmI(){return "TFObject";}
#endif
protected:
    TFObject();
    void clearThis();
    
    bool m_isDead;
private:
};

#endif /* defined(__TheForce__TFObject__) */
