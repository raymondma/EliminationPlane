//
//  TFObjectFactory.cpp
//  EliminationPlane
//
//  Created by Ray M on 13-4-3.
//
//

#include "TFObjectFactory.h"
#include "TFObject.h"
#include "TFRole.h"
#include "TFBulletBase.h"
#include "TFMonster.h"
#include "TFItemInGame.h"
#include "TFHPBar.h"
#include "TFGun.h"
#include "TFScale9SpriteObject.h"
#include "EPPlane.h"

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
    REGISTER_CLASS(TFRole);
    REGISTER_CLASS(TFBulletBase);
    REGISTER_CLASS(TFMonster);
    REGISTER_CLASS(TFItemInGame);
    REGISTER_CLASS(TFHPBar);
    REGISTER_CLASS(TFGun);
    REGISTER_CLASS(TFScale9SpriteObject);
    REGISTER_CLASS(EPPlane);
    return true;
}



bool TFObjectFactory::registerClass(const string&  className, FACTORY_CREATE_FUNC func)
{
    if (!func)
    {
        return false;
    }
    
    MSCF_CIT it = pFactoryTable.find(className);
    if (it != pFactoryTable.end())
    {
        return false;
    }
    pFactoryTable[className] = func;
    return true;
}



TFObject* TFObjectFactory::createInstance(const string& className)
{
    MSCF_IT it = pFactoryTable.find(className);
    if (it == pFactoryTable.end())
    {
        return NULL;
    }
    
    return ((*it).second)();
}



