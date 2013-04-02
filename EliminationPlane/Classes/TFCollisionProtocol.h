//
//  TFCollisionProtocol.h
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFCollisionProtocol__
#define __TheForce__TFCollisionProtocol__


class TFObject;

class TFCollisionProtocol
{
public:
    virtual void checkCollision(TFCollisionProtocol* rb);
    
    virtual bool isCollsionWith(TFCollisionProtocol* rb);
    virtual bool isNeedCheckCollision();
    virtual int getCollisionGroup();
    virtual void turnOffCollision();
    virtual void turnOnCollision();
protected:
private:
};

#endif /* defined(__TheForce__TFCollisionProtocol__) */
