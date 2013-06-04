//
//  EPPlane.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-4-1.
//
//

#ifndef __EliminationPlane__EPPlane__
#define __EliminationPlane__EPPlane__

#include "CRole.h"
#include "TFObjectFactory.h"

class EPPlane : public CRole
{
public:
    FACTORY_CREATE_FUNC(EPPlane);
    
    virtual ~EPPlane();
    
    virtual void update(float dt);
    virtual void clearAll();
    
    virtual void doubleGun(float duration);
    virtual void cancelDoubleGun();

    virtual void MoveDelta(float x);
    
    virtual void checkCollision(TFCollisionProtocol* rb);
    
    virtual void triggerSkill();
#ifdef DEBUG
    virtual string whoAmI(){return "EPPlane";}
#endif
    
protected:
    EPPlane();
    
    void clearThis();
    void updateDoubleGun(float dt);
    
    bool m_isDoubleGun;
    float m_doubleGunStartTime;
    float m_doubleGunDuration;
    
private:
};

#endif /* defined(__EliminationPlane__EPPlane__) */
