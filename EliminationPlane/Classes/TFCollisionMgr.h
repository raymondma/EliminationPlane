//
//  TFCollisionMgr.h
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFCollisionMgr__
#define __TheForce__TFCollisionMgr__

#include "cocos2d.h"
#include "TFSingleton.h"

#include <map>
#include <set>

USING_NS_CC;
using namespace std;


class TFCollisionProtocol;

class TFCollisionMgr : public TFSingleton<TFCollisionMgr>
{
public:
    TFCollisionMgr();
    virtual ~TFCollisionMgr();

    virtual bool registerCollisionObj(TFCollisionProtocol* pRB, int group);
    virtual void unregisterCollisionObj(TFCollisionProtocol* pRB, int group);

    virtual void update();
    virtual void clearAll();
    
protected:
    typedef set<TFCollisionProtocol*> LRB;
    typedef set<TFCollisionProtocol*>::iterator LRB_IT;
    typedef set<TFCollisionProtocol*>::const_iterator LRB_CIT;
    
    typedef map<int, LRB> MILRB;
    typedef map<int, LRB>::iterator MILRB_IT;
    typedef map<int, LRB>::const_iterator MILRB_CIT;

   
    
    MILRB m_ToBeAdded;
    MILRB m_ToBeDeleted;
    MILRB m_CollisionObjs;
    
    virtual void updateToBeAdded();
    virtual void updateToBeDeleted();
    
private:
};

#define COLLISION_MANAGER (TFCollisionMgr::getInstance())

#endif /* defined(__TheForce__TFCollisionMgr__) */
