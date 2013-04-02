//
//  TFCollisionProtocol.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFCollisionProtocol.h"
#include "TFCollisionMgr.h"

void TFCollisionProtocol::turnOnCollision()
{
    if (COLLISION_MANAGER)
    {
        COLLISION_MANAGER->registerCollisionObj(dynamic_cast<TFCollisionProtocol*>(this), getCollisionGroup());
    }
}



void TFCollisionProtocol::turnOffCollision()
{
    if (COLLISION_MANAGER)
    {
        COLLISION_MANAGER->unregisterCollisionObj(dynamic_cast<TFCollisionProtocol*>(this), getCollisionGroup());
    }
}



int TFCollisionProtocol::getCollisionGroup()
{
    return 0;
}



bool TFCollisionProtocol::isCollsionWith(TFCollisionProtocol* rb)
{
    return false;
}



bool TFCollisionProtocol::isNeedCheckCollision()
{
    return false;
}



void TFCollisionProtocol::checkCollision(TFCollisionProtocol* rb)
{
    
}
