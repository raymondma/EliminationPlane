//
//  TFObjectFactory.cpp
//  EliminationPlane
//
//  Created by Ray M on 13-4-3.
//
//

#include "TFObjectFactory.h"
#include "CObjectBase.h"
#include "CRole.h"
#include "CBulletBase.h"
#include "TFMonster.h"
#include "TFItemInGame.h"
#include "TFHPBar.h"
#include "CGun.h"
#include "CScale9SpriteObject.h"
#include "CSpriteObject.h"
#include "EPPlane.h"
#include "EPLand.h"

#define REGISTER_CLASS(__classname) if (!registerClass(#__classname, FACTOR_SEL(__classname::create))){return false;}
#define FACTOR_SEL(__selector) (FACTORY_CREATE_FUNC)(&__selector)


IMPLEMENT_SINGLETON(TFObjectFactory)

TFObjectFactory::TFObjectFactory()
{

}



TFObjectFactory::~TFObjectFactory()
{
    
}


bool TFObjectFactory::Initialize()
{
    REGISTER_CLASS(CRole);
    REGISTER_CLASS(CBulletBase);
    REGISTER_CLASS(TFMonster);
    REGISTER_CLASS(TFItemInGame);
    REGISTER_CLASS(TFHPBar);
    REGISTER_CLASS(CGun);
    REGISTER_CLASS(CSpriteObject);
    REGISTER_CLASS(CScale9SpriteObject);
    REGISTER_CLASS(EPPlane);
    REGISTER_CLASS(EPLand);
    return true;
}



bool TFObjectFactory::registerClass(const string&  className, FACTORY_CREATE_FUNC func)
{
    if (!func)
    {
        return false;
    }
    
    MSCF_CIT it = FactoryTable_.find(className);
    if (it != FactoryTable_.end())
    {
        return false;
    }
    FactoryTable_[className] = func;
    return true;
}



CObjectBase* TFObjectFactory::createInstance(const string& className)
{
    MSCF_IT it = FactoryTable_.find(className);
    if (it == FactoryTable_.end())
    {
        return NULL;
    }
    
    return ((*it).second)();
}



