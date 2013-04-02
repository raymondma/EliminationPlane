//
//  TFSpriteActionDelegate.h
//  TheForce
//
//  Created by Ray M on 13-3-18.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef TheForce_TFSpriteActionDelegate_h
#define TheForce_TFSpriteActionDelegate_h

class TFSpriteObject;

class TFSpriteActionDelegate
{
public:
    virtual void completedAction(TFSpriteObject* pObj, const char* name) = 0;
};

#endif
