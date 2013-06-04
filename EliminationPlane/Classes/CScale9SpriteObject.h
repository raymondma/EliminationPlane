//
//  CScale9SpriteObject.h
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFScale9SpriteObject__
#define __TheForce__TFScale9SpriteObject__

#include "CVisibleObject.h"

class CScale9SpriteObject : public CVisibleObject
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(CScale9SpriteObject);
	virtual ~CScale9SpriteObject();
	
	virtual bool init(CCDictionary* pObjectDict);
    virtual bool init(const string& name);
    
    virtual void clearAll();
    
 
    virtual void setSpritePreferredSize(const CCSize& size);
    
    DECLARE_DICTFUNC(CCString*, FileName);
protected:
    CScale9SpriteObject();
    void clearThis();
    
    virtual CCNode* getInnerSprite() const;
    
    bool createScale9Sprite(const string& name);
    
    CCScale9Sprite* m_pSprite;
    
    
private:
};


#endif /* defined(__TheForce__TFScale9SpriteObject__) */
