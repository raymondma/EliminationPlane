//
//  TFTexturesCache.h
//  TheForce
//
//  Created by Ming Zhao on 2/2/13.
//  Copyright (c) 2013 Tencent All rights reserved.
//

#ifndef __TheForce__TFTexturesCache__
#define __TheForce__TFTexturesCache__

#include "cocos2d.h"
#include "Common.h"

USING_NS_CC;
using namespace std;

class TFTexturesCache
{
public:
    static TFTexturesCache* getInstance();
    
    void addTextures(const string& suffix);
    CCSpriteBatchNode* createSpriteBatchNode(GameArts gameArt, int capacity = kDefaultSpriteBatchCapacity);
    
    /**
     @deprecated: This interface will be deprecated sooner or later.
     */
    CC_DEPRECATED_ATTRIBUTE CCSpriteBatchNode* createSpriteBatchNode(const string& fname, int capacity = kDefaultSpriteBatchCapacity);
    
    string getFontFileName(GameFonts gameFont) const;
    
protected:
private:
    string m_suffix;
    static TFTexturesCache* m_spTextureCache;
    
    TFTexturesCache();
    ~TFTexturesCache();
};

#define TEXTURE_CACHE (TFTexturesCache::getInstance())

#endif /* defined(__TheForce__TFTexturesCache__) */
