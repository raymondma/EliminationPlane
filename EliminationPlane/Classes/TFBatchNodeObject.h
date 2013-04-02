//
//  TFBatchNodeObject.h
//  TheForce
//
//  Created by 马 俊 on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFBatchNodeObject__
#define __TheForce__TFBatchNodeObject__

#include "TFObject.h"
#include "TFTexturesCache.h"

class TFBatchNodeObject
{
    CC_SYNTHESIZE_RETAIN(CCSpriteBatchNode*, pBatchNode_, BatchNode);
public:
    TFBatchNodeObject();
    virtual ~TFBatchNodeObject();
    virtual bool init();
    virtual bool attachBatchNodeToParent(CCNode* parent, int zOrder=0, int tag=-1);
    virtual void clearAllBatchNode();
protected:
    virtual GameArts getBatchNodeName()=0;
private:
};

#endif /* defined(__TheForce__TFBatchNodeObject__) */
