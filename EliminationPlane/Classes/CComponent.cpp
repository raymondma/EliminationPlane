//
//  CComponent.cpp
//  GingyBattle
//
//  Created by 马 俊 on 13-4-23.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CComponent.h"


CComponent::CComponent()
: m_pTarget(NULL)
{
    
}



CComponent::~CComponent()
{
    setTarget(NULL);
}



void CComponent::onEnterComponent()
{

}



void CComponent::onLeaveComponent()
{

}
