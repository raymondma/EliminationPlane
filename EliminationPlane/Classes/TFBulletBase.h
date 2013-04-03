//
//  TFBulletBase.h
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

#include "TFSpriteObject.h"

USING_NS_CC;
using namespace std;

class TFRole;

class TFBulletBase : public TFSpriteObject
{
    friend class TFObject;
public:
    FACTORY_CREATE_FUNC(TFBulletBase);
    virtual ~TFBulletBase();
    
    virtual bool init(CCDictionary* pObjectDict);
    virtual void update(float dt);

    virtual void checkCollision(TFCollisionProtocol* rb);
    
    virtual float getDamage();

#ifdef DEBUG
    virtual string whoAmI(){return "TFBulletBase";}
#endif
    
    DECLARE_DICTFUNC(float, Damage);
    DECLARE_DICTFUNC(float, Speed);
protected:
    TFBulletBase();
    float m_speed;
private:

};


#endif /* defined(__TheForce__TFBulletBase__) */
