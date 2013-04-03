//
//  TFCollisionMgr.cpp
//  TheForce
//
//  Created by 马 俊 on 13-2-3.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFCollisionMgr.h"
#include "TFCollisionProtocol.h"


IMPLEMENT_SINGLETON(TFCollisionMgr);





TFCollisionMgr::TFCollisionMgr()
{
    
}



TFCollisionMgr::~TFCollisionMgr()
{
    clearAll();
}



bool TFCollisionMgr::registerCollisionObj(TFCollisionProtocol* pRB, int group)
{
    if (group != 1 && group != 2)
    {
        return false;
    }
    
    m_ToBeAdded[group].insert(pRB);
    
    LRB_IT it = m_ToBeDeleted[group].find(pRB);
    if (it != m_ToBeDeleted[group].end())
    {
        m_ToBeDeleted[group].erase(it);
    }
    return true;
}



void TFCollisionMgr::unregisterCollisionObj(TFCollisionProtocol* pRB, int group)
{
    if (group != 1 && group != 2)
    {
        return;
    }
    
    m_ToBeDeleted[group].insert(pRB);

    LRB_IT it = m_ToBeAdded[group].find(pRB);
    if (it != m_ToBeAdded[group].end())
    {
        m_ToBeAdded[group].erase(it);
    }
    return;
}



void TFCollisionMgr::update()
{
    updateToBeAdded();
    updateToBeDeleted();
    
//    CCLog("CollisionObj 1: %d, 2: %d", m_CollisionObjs[1].size(), m_CollisionObjs[2].size());

    LRB_IT it1 = m_CollisionObjs[1].begin();

    for (; it1!=m_CollisionObjs[1].end(); ++it1)
    {
        TFCollisionProtocol* c1 = *it1;

        if (!c1->isNeedCheckCollision())
        {
            continue;
        }
        
        LRB_IT it2 = m_CollisionObjs[2].begin();
        for (; it2!=m_CollisionObjs[2].end(); ++it2)
        {
            
            TFCollisionProtocol* c2 = *it2;
            if (c1 == c2)
            {
                continue;
            }
            
            if (!c2->isNeedCheckCollision())
            {
                continue;
            }

            if (c1->isCollsionWith(c2))
            {
                c1->checkCollision(c2);
                c2->checkCollision(c1);
            }
        }
    }
}



void TFCollisionMgr::clearAll()
{
    m_CollisionObjs.clear();
    m_ToBeDeleted.clear();
    m_ToBeAdded.clear();
}



void TFCollisionMgr::updateToBeAdded()
{
    MILRB_IT it = m_ToBeAdded.begin();
    for (; it != m_ToBeAdded.end(); ++it)
    {
        m_CollisionObjs[(*it).first].insert((*it).second.begin(), (*it).second.end());
    }
    m_ToBeAdded.clear();
}



void TFCollisionMgr::updateToBeDeleted()
{
    MILRB_IT it = m_ToBeDeleted.begin();
    for (; it!=m_ToBeDeleted.end(); ++it)
    {
        MILRB_IT collisionObj_it = m_CollisionObjs.find((*it).first);
        if (collisionObj_it == m_CollisionObjs.end()) continue;
        
        LRB& collisionObjSet = (*collisionObj_it).second;
        
        LRB_IT sit = (*it).second.begin();
        for (; sit != (*it).second.end(); ++sit)
        {
            LRB_IT fit = collisionObjSet.find(*sit);
            if (fit != collisionObjSet.end())
            {
                collisionObjSet.erase(fit);
            }
        }
    }
    m_ToBeDeleted.clear();
}
