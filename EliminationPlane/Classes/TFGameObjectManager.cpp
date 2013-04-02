//
//  TFGameObjectManager.cpp
//  TheForce
//
//  Created by Ray M on 13-3-6.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFGameObjectManager.h"

TFGameObjectManager* TFGameObjectManager::spInstance_ = NULL;




TFGameObjectManager* TFGameObjectManager::getInstance()
{
    if (!spInstance_)
    {
        spInstance_ = new TFGameObjectManager;
    }
    
    return spInstance_;
}


TFGameObjectManager::TFGameObjectManager() :
pGameObjects_(NULL)
{

}



TFGameObjectManager::~TFGameObjectManager()
{
    spInstance_ = NULL;
    clearAll();
}



void TFGameObjectManager::clearAll()
{
    setGameObjects(NULL);
}



bool TFGameObjectManager::init()
{
    clearAll();
    
    const char* cp = "GameObject.plist";
	const char* fcp = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(cp);
    
	setGameObjects(CCDictionary::createWithContentsOfFile(fcp));
    if (!getGameObjects())
    {
        __CCLOGWITHFUNCTION("file can't be loaded: %s", fcp);
        return false;
    }
    
    return true;
}



CCDictionary* TFGameObjectManager::getObjectByName(const string& name)
{
    if (NULL == pGameObjects_)
    {
        __CCLOGWITHFUNCTION("has not initialized!");
        return NULL;
    }
    
    return  dynamic_cast<CCDictionary*>(pGameObjects_->objectForKey(name));
}
