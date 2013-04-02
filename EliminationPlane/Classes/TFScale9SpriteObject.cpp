//
//  TFScale9SpriteObject.cpp
//  TheForce
//
//  Created by Ray M on 13-3-5.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFScale9SpriteObject.h"

DEFINE_DICTFUNC_STR(TFScale9SpriteObject, FileName);


TFScale9SpriteObject::TFScale9SpriteObject() :
m_pSprite(NULL)
{
    
}



TFScale9SpriteObject::~TFScale9SpriteObject()
{
    clearThis();
}



bool TFScale9SpriteObject::init(CCDictionary* pObjectDict)
{
    if (!TFVisibleObject::init(pObjectDict))
    {
        return false;
    }
    
    CCString* filename = getFileNameFromDict();
    if (NULL == filename)
    {
        return false;
    }
    
    if (!createScale9Sprite(filename->getCString()))
    {
        return false;
    }
    return true;
}



bool TFScale9SpriteObject::init(const string& name)
{
    if (!TFVisibleObject::init(NULL))
    {
        return false;
    }
    
    if (!createScale9Sprite(name))
    {
        return false;
    }
    
    return true;
}



bool TFScale9SpriteObject::createScale9Sprite(const string& name)
{
    string _name = name;
    string::size_type pos = name.find(".png", 0);
    if (pos != string::npos)
    {
        _name = name.substr(0, pos);
    }
    
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name.c_str());
    if (NULL == pFrame)
    {
        return false;
    }
//    OrigBarSize_ = pFrame->getRect().size;
    m_pSprite = CCScale9Sprite::createWithSpriteFrameName(_name.c_str(), pFrame->getRect());
    if (NULL == m_pSprite)
    {
        return false;
    }
    
    return true;
}



void TFScale9SpriteObject::clearAll()
{
    TFVisibleObject::clearAll();
    
    clearThis();
}



void TFScale9SpriteObject::clearThis()
{
    if (m_pSprite)
    {
        m_pSprite->removeFromParentAndCleanup(true);
        m_pSprite = NULL;
    }
}



void TFScale9SpriteObject::setSpritePreferredSize(const CCSize& size)
{
    if (NULL != m_pSprite)
    {
        m_pSprite->setPreferredSize(size);
    }
}



CCNode* TFScale9SpriteObject::getInnerSprite() const
{
    return m_pSprite;
}

