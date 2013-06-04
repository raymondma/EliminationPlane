//
//  TFPathManager.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#include "TFPathManager.h"
#include "TFPath.h"

IMPLEMENT_SINGLETON(TFPathManager);


TFPathManager::TFPathManager()
: paths_(NULL)
{
    
}



TFPathManager::~TFPathManager()
{
    setPaths(NULL);
}



bool TFPathManager::initialize()
{
    do
    {
        setPaths(CCArray::create());
        CC_BREAK_IF(!paths_);
        
        const char* cp = "test.pm";
        const char* fcp = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(cp);
        
        FILE* fp = fopen(fcp, "rb");
        CC_BREAK_IF(NULL == fp);
        
        CCArray* controlPoint = CCArray::create();
        
        double x, y;
        fseek(fp, 0, SEEK_END);
        int len = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        
        len /= 2 * sizeof(double);
        for (int i = 0; i < len; ++i)
        {
            fread(&x, sizeof(double), 1, fp);
            fread(&y, sizeof(double), 1, fp);
            CCPoint* pt = new CCPoint(x, y);

            pt->autorelease();
            controlPoint->addObject(pt);
        }
        fclose(fp);
        
        TFPath* path = new TFPath;
        path->autorelease();
        CC_BREAK_IF(!path->init(controlPoint));
        paths_->addObject(path);
        return true;
    }while (false);
        
    return false;
}



TFPath* TFPathManager::getPath()
{
    return dynamic_cast<TFPath*>(paths_->objectAtIndex(0));
}
