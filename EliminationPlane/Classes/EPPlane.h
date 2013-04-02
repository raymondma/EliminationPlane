//
//  EPPlane.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-4-1.
//
//

#ifndef __EliminationPlane__EPPlane__
#define __EliminationPlane__EPPlane__

#include "TFRole.h"

class EPPlane : public TFRole
{
    friend class TFObject;
public:
    virtual ~EPPlane();
    
    virtual void update(float dt);
    virtual void clearAll();
    
    virtual void triggerSkill();
#ifdef DEBUG
    virtual string whoAmI(){return "EPPlane";}
#endif
    
protected:
    EPPlane();
    
};

#endif /* defined(__EliminationPlane__EPPlane__) */
