//
//  TFMonsterData.h
//  TheForce
//
//  Created by Ray M on 13-2-20.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFMonsterData__
#define __TheForce__TFMonsterData__

#include <string>

using namespace std;

#define MAX_MONSTER_IN_A_LINE 5

class TFMonsterData
{
public:
    static float MonsterPosInLine[MAX_MONSTER_IN_A_LINE];
    float Pos;
    string MonsterLine[MAX_MONSTER_IN_A_LINE];
protected:
private:
};

#endif /* defined(__TheForce__TFMonsterData__) */
