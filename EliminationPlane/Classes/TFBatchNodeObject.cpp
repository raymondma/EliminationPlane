//
//  TFBatchNodeObject.cpp
//  TheForce
//
//  Created by 马 俊 on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFBatchNodeObject.h"
#include "TFTexturesCache.h"


TFBatchNodeObject::TFBatchNodeObject() :
pBatchNode_(NULL)
{
    
}



TFBatchNodeObject::~TFBatchNodeObject()
{
    clearAllBatchNode();
}



bool TFBatchNodeObject::init()
{
    setBatchNode(TEXTURE_CACHE->createSpriteBatchNode(getBatchNodeName()));
    if (NULL == getBatchNode())
    {
        return false;
    }
    
    return true;
}



void TFBatchNodeObject::clearAllBatchNode()
{
    if (getBatchNode())
    {
        getBatchNode()->removeFromParentAndCleanup(true);
    }
    setBatchNode(NULL);
}



bool TFBatchNodeObject::attachBatchNodeToParent(CCNode* parent, int zOrder, int tag)
{
    if (NULL == parent)
    {
        __CCLOGWITHFUNCTION("parent can't be NULL");
        return false;
    }
    
    parent->addChild(getBatchNode(), zOrder, tag);
    return true;
}
