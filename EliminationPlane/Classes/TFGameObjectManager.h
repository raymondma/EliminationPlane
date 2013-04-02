//
//  TFGameObjectManager.h
//  TheForce
//
//  Created by Ray M on 13-3-6.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFGameObjectManager__
#define __TheForce__TFGameObjectManager__

#include "cocos2d.h"

#include <string>

using namespace std;
USING_NS_CC;

class TFGameObjectManager
{
    CC_SYNTHESIZE_RETAIN(CCDictionary*, pGameObjects_, GameObjects);
public:
    ~TFGameObjectManager();
    static TFGameObjectManager* getInstance();
    
    bool init();
    void clearAll();
    
    CCDictionary* getObjectByName(const string& name);

protected:
    TFGameObjectManager();
private:
    static TFGameObjectManager* spInstance_;
};

#define GAME_OJBECT_MANAGER (TFGameObjectManager::getInstance())

#endif /* defined(__TheForce__TFGameObjectManager__) */
