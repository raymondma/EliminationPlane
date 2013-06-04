//
//  TFPathManager.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#ifndef __EliminationPlane__TFPathManager__
#define __EliminationPlane__TFPathManager__

#include "cocos2d.h"
#include "TFSingleton.h"

USING_NS_CC;

class TFPath;


class TFPathManager : public TFSingleton<TFPathManager>
{
    CC_SYNTHESIZE_RETAIN(CCArray*, paths_, Paths);
public:
    TFPathManager();
    virtual ~TFPathManager();
    virtual bool initialize();
    
    virtual TFPath* getPath();
protected:

private:
};


#define PATH_MANAGER (TFPathManager::getInstance())

#endif /* defined(__EliminationPlane__TFPathManager__) */
