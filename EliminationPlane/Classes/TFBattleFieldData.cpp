//
//  TFBattleFieldData.cpp
//  TheForce
//
//  Created by Ray M on 13-2-20.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//
#include "cocos2d.h"

#include "TFBattleFieldData.h"

USING_NS_CC;



TFBattleFieldData::TFBattleFieldData()
{
    
}



TFBattleFieldData::~TFBattleFieldData()
{
    clearMonsters();
}



void TFBattleFieldData::clearMonsters()
{
    VM_IT it = m_Monsters.begin();
    for (; it!=m_Monsters.end(); ++it)
    {
        CC_SAFE_DELETE(*it);
    }
    m_Monsters.clear();
}


