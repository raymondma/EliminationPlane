//
//  TFNodeContainer.h
//  TheForce
//
//  Created by 马 俊 on 13-2-21.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFBatchNodeBase__
#define __TheForce__TFBatchNodeBase__

#include "cocos2d.h"

#include <string>

using namespace std;
USING_NS_CC;

class TFObject;

class TFNodeContainer
{
public:
    TFNodeContainer();
    virtual ~TFNodeContainer();
    
    const CCArray* getInUseArray() const;
    unsigned int  getInUseCount();
    virtual bool initCache(const string& name, int num);
    virtual TFObject* checkoutElement();
    virtual void checkinElement(TFObject* elem);
    virtual void clear();

protected:
private:
    CCArray containerInUseArray_;
    CCArray containerUnUseArray_;
};

#endif /* defined(__TheForce__TFBatchNodeBase__) */
