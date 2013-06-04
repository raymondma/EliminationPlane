//
//  EPLand.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-4-5.
//
//

#ifndef __EliminationPlane__EPLand__
#define __EliminationPlane__EPLand__

#include "CRole.h"

class EPLand : public CSpriteObject
{
public:
    FACTORY_CREATE_FUNC(EPLand);
    virtual ~EPLand();
    
    virtual void checkCollision(TFCollisionProtocol* rb);
protected:
    EPLand();
private:
};

#endif /* defined(__EliminationPlane__EPLand__) */
