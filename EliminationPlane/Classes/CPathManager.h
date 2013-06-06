//
//  CPathManager.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#ifndef __EliminationPlane__TFPathManager__
#define __EliminationPlane__TFPathManager__

#include "cocos2d.h"
#include "TFSingleton.h"
#include <string>

using namespace std;
USING_NS_CC;

class CPath;

class CPathManager : public TFSingleton<CPathManager>
{
    CC_SYNTHESIZE_RETAIN(CCDictionary*, paths_, Paths);
public:
    CPathManager();
    virtual ~CPathManager();
    virtual bool initialize();
    
    virtual CPath* getPathByName(const string& name);
protected:

private:
};


#define PATH_MANAGER (CPathManager::getInstance())

#endif /* defined(__EliminationPlane__TFPathManager__) */
