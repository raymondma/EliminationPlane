//
//  CComponentParameter.cpp
//  GingyBattle
//
//  Created by 马 俊 on 13-4-23.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "CComponentParameter.h"


CComponentParameter::CComponentParameter()
: parameters_(NULL)
{
    
}



CComponentParameter::~CComponentParameter()
{
    setParameters(NULL);
}



bool CComponentParameter::init()
{
    do
    {
        setParameters(CCDictionary::create());
        CC_BREAK_IF(!getParameters());
        return true;
    } while (false);
    return false;
}



bool CComponentParameter::addObjectParameter(const string& name, CCObject* value)
{
    parameters_->setObject(value, name);
    return true;
}



bool CComponentParameter::addStringParameter(const string& name, const string& value)
{
    CCString* str = CCString::create(value);
    parameters_->setObject(str, name);
    return true;
}



bool CComponentParameter::addIntParameter(const string& name, int value)
{
    CCString* str = CCString::createWithFormat("%d", value);
    parameters_->setObject(str, name);
    return true;
}



bool CComponentParameter::addFloatParameter(const string& name, float value)
{
    CCString* str = CCString::createWithFormat("%f", value);
    parameters_->setObject(str, name);
    return true;
}



bool CComponentParameter::addBoolParameter(const string& name, bool value)
{
    CCString* str = CCString::createWithFormat("%s", value ? "YES" : "NO");
    parameters_->setObject(str, name);
    return true;
}



bool CComponentParameter::getObjectParameter(const string& name, CCObject** value)
{
    *value = parameters_->objectForKey(name);
    
    if (*value)
    {
        return true;
    }
    return false;
}



bool CComponentParameter::getStringParameter(const string& name, string& value)
{
    CCString* str = dynamic_cast<CCString*>(parameters_->objectForKey(name));
    if (!str)
    {
        return false;
    }
    value = str->getCString();
    
    return true;
}



bool CComponentParameter::getIntParameter(const string& name, int& value)
{
    CCString* str = dynamic_cast<CCString*>(parameters_->objectForKey(name));
    if (!str)
    {
        return false;
    }
    value = str->intValue();
    
    return true;
}



bool CComponentParameter::getFloatParameter(const string& name, float& value)
{
    CCString* str = dynamic_cast<CCString*>(parameters_->objectForKey(name));
    if (!str)
    {
        return false;
    }
    value = str->floatValue();
    
    return true;
}



bool CComponentParameter::getBoolParameter(const string& name, bool& value)
{
    CCString* str = dynamic_cast<CCString*>(parameters_->objectForKey(name));
    if (!str)
    {
        return false;
    }
    value = str->boolValue();
    
    return true;
}



