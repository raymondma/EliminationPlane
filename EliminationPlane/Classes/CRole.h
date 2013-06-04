//
//  CRole
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#ifndef __TheForce__TFRole__
#define __TheForce__TFRole__

#include "cocos2d.h"
#include "CSpriteObject.h"
#include "CGun.h"


USING_NS_CC;

class CRole : public CSpriteObject
{
    friend class CObjectBase;
    CC_SYNTHESIZE_RETAIN(CGun*, m_pGun, Gun);
public:
    FACTORY_CREATE_FUNC(CRole);
    
	virtual ~CRole();

    virtual bool init(CCDictionary* pObjectDict);

	virtual CCPoint getShootPoint();
	virtual void update(float dt);
    virtual void clearAll();
    virtual bool createGun(const string& name);
    virtual bool changeBullet(const string& name);
    
    virtual bool attachSpriteTo(CCNode* parent, int zOrder=0, int tag=-1);
    
    DECLARE_DICTFUNC(CCDictionary*, Gun);
protected:
	CRole();
    void clearThis();
    
    void updateShootPointInWorldSpace();

	CCPoint m_shootPoint;
    CCPoint m_shootPointInWorldSpace;

private:
    
};

#endif /* defined(__TheForce__TFRole__) */
