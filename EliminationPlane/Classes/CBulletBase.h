//
//  CBulletBase.h
//  TheForce
//
//  Created by 马 俊 on 13-1-11.
//
//

#ifndef __TheForce__TFBulletBase__
#define __TheForce__TFBulletBase__

#include "cocos2d.h"
#include <string>
#include <vector>

#include "CSpriteObject.h"

USING_NS_CC;
using namespace std;

class CRole;

class CBulletBase : public CSpriteObject
{
    friend class CObjectBase;
public:
    FACTORY_CREATE_FUNC(CBulletBase);
    virtual ~CBulletBase();
    
    virtual bool init(CCDictionary* pObjectDict);
    virtual void update(float dt);

    virtual void checkCollision(TFCollisionProtocol* rb);
    
    virtual float getDamage();

#ifdef DEBUG
    virtual string whoAmI(){return "CBulletBase";}
#endif
    
    DECLARE_DICTFUNC(float, Damage);
    DECLARE_DICTFUNC(float, Speed);
protected:
    CBulletBase();
    float m_speed;
private:

};


#endif /* defined(__TheForce__TFBulletBase__) */
