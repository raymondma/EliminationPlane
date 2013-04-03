//
//  TFObjectFactory.h
//  EliminationPlane
//
//  Created by Ray M on 13-4-3.
//
//

#ifndef __EliminationPlane__TFObjectFactory__
#define __EliminationPlane__TFObjectFactory__

#include "TFSingleton.h"

#include <map>
#include <string>

class TFObject;

using namespace std;


class TFObjectFactory : public TFSingleton<TFObjectFactory>
{
public:
    typedef TFObject* (*FACTORY_CREATE_FUNC)();

    TFObjectFactory();
    virtual ~TFObjectFactory();
    
    bool Initialize();
    TFObject* createInstance(const string& className);
    
protected:
    bool registerClass(const string&  className, FACTORY_CREATE_FUNC func);
private:
    typedef map<string, FACTORY_CREATE_FUNC> MSCF;
    typedef map<string, FACTORY_CREATE_FUNC>::iterator MSCF_IT;
    typedef map<string, FACTORY_CREATE_FUNC>::const_iterator MSCF_CIT;
    
    MSCF pFactoryTable;
    
};

#define FACTORY_CREATE_FUNC(__type) static TFObject* create() \
{ \
    __type *pRet = new __type(); \
    if (pRet) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define OBJECT_FACTORY (TFObjectFactory::getInstance())


#endif /* defined(__EliminationPlane__TFObjectFactory__) */
