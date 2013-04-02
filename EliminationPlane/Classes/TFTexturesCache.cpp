//
//  TFSpriteBatchNodeCache.cpp
//  TheForce
//
//  Created by Ming Zhao on 2/2/13.
//  Copyright (c) 2013 Tencent All rights reserved.
//

#include "TFTexturesCache.h"
#include <stdio.h>

TFTexturesCache* TFTexturesCache::m_spTextureCache = NULL;


TFTexturesCache::TFTexturesCache()
{
}



TFTexturesCache::~TFTexturesCache()
{
    
}



TFTexturesCache* TFTexturesCache::getInstance()
{
    if(!m_spTextureCache)
    {
        m_spTextureCache = new TFTexturesCache();
        
        CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    }
    
    return m_spTextureCache;
}



void TFTexturesCache::addTextures(const string& suffix)
{
    m_suffix = suffix;
    
    char buffer[256] = {0};
    // Add frame cache
    for (int i = 0; i < GAME_ARTS_MAX; i++)
    {
        string fname = GAME_ARTS_TEXT(i);
        CCSpriteFrameCache* sfc = CCSpriteFrameCache::sharedSpriteFrameCache();
        sprintf(buffer, "%s%s.plist", fname.c_str(), m_suffix.c_str());
        sfc->addSpriteFramesWithFile(buffer);
    }
    
    // Add font cache for bmfont
    for (int i = 0; i < GAME_FONTS_MAX; i++)
    {
        string fname = GAME_FONTS_TEXT(i);
        sprintf(buffer, "%s%s.fnt", fname.c_str(), m_suffix.c_str());
        CCBMFontConfiguration::create(buffer);
    }
}


CCSpriteBatchNode* TFTexturesCache::createSpriteBatchNode(GameArts gameArt, int capacity)
{
    char buffer[256] = {0};
    string fname = GAME_ARTS_TEXT(gameArt);
    sprintf(buffer, "%s%s.pvr.ccz", fname.c_str(), m_suffix.c_str());
    return CCSpriteBatchNode::create(buffer, capacity);
}


CCSpriteBatchNode* TFTexturesCache::createSpriteBatchNode(const string& fname, int capacity)
{
    char buffer[256] = {0};
    sprintf(buffer, "%s%s.pvr.ccz", fname.c_str(), m_suffix.c_str());
    return CCSpriteBatchNode::create(buffer, capacity);
}


string TFTexturesCache::getFontFileName(GameFonts gameFont) const
{
    char buffer[256] = {0};
    string fname = GAME_FONTS_TEXT(gameFont);
    sprintf(buffer, "%s%s.fnt", fname.c_str(), m_suffix.c_str());
    
    return buffer;
}
