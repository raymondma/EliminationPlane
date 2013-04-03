//
//  TFRole
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#ifndef __TheForce__TFRole__
#define __TheForce__TFRole__

#include "cocos2d.h"
#include "TFSpriteObject.h"
#include "TFGun.h"


USING_NS_CC;

class TFRole : public TFSpriteObject
{
    friend class TFObject;
    CC_SYNTHESIZE_RETAIN(TFGun*, m_pGun, Gun);
public:
    FACTORY_CREATE_FUNC(TFRole);
    
	virtual ~TFRole();

    virtual bool init(CCDictionary* pObjectDict);

	virtual CCPoint getShootPoint();
	virtual void update(float dt);
    virtual void clearAll();
    virtual bool createGun(const string& name);
    virtual bool changeBullet(const string& name);
    
    virtual bool attachSpriteTo(CCNode* parent, int zOrder=0, int tag=-1);
    
    DECLARE_DICTFUNC(CCDictionary*, Gun);
protected:
	TFRole();
    void clearThis();
    
    void updateShootPointInWorldSpace();

	CCPoint m_shootPoint;
    CCPoint m_shootPointInWorldSpace;

private:
    
};

#endif /* defined(__TheForce__TFRole__) */
