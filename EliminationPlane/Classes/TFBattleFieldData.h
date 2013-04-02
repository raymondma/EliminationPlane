//
//  TFBattleFieldData.h
//  TheForce
//
//  Created by Ray M on 13-2-20.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#ifndef __TheForce__TFBattleFieldData__
#define __TheForce__TFBattleFieldData__

#include <string>
#include <vector>

#include "TFMonsterData.h"

class TFMonster;

class TFBattleFieldData
{
public:
    TFBattleFieldData();
    virtual ~TFBattleFieldData();
    
    void clearMonsters();
    
    string m_Name;
    float m_StartPosX;
    float m_StartPosY;
    
    typedef vector<TFMonsterData*> VM;
    typedef vector<TFMonsterData*>::iterator VM_IT;
    typedef vector<TFMonsterData*>::const_iterator VM_CIT;
    
    VM m_Monsters;
protected:
private:
};


#endif /* defined(__TheForce__TFBattleFieldData__) */
