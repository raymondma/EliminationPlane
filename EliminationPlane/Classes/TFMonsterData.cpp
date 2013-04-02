//
//  TFMonsterData.cpp
//  TheForce
//
//  Created by Ray M on 13-2-20.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFMonsterData.h"

#define MONSTER_SPACE 60

float TFMonsterData::MonsterPosInLine[MAX_MONSTER_IN_A_LINE] =
{
    160-MONSTER_SPACE*2,
    160-MONSTER_SPACE,
    160,
    160+MONSTER_SPACE,
    160+MONSTER_SPACE*2,
};
