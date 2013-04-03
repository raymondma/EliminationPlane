//
//  TFScale9SpriteObject.h
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFScale9SpriteObject__
#define __TheForce__TFScale9SpriteObject__

#include "TFVisibleObject.h"

class TFScale9SpriteObject : public TFVisibleObject
{
    friend class TFObject;
public:
    FACTORY_CREATE_FUNC(TFScale9SpriteObject);
	virtual ~TFScale9SpriteObject();
	
	virtual bool init(CCDictionary* pObjectDict);
    virtual bool init(const string& name);
    
    virtual void clearAll();
    
 
    virtual void setSpritePreferredSize(const CCSize& size);
    
    DECLARE_DICTFUNC(CCString*, FileName);
protected:
    TFScale9SpriteObject();
    void clearThis();
    
    virtual CCNode* getInnerSprite() const;
    
    bool createScale9Sprite(const string& name);
    
    CCScale9Sprite* m_pSprite;
    
    
private:
};


#endif /* defined(__TheForce__TFScale9SpriteObject__) */
