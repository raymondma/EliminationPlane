//
//  CPathManager.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-3.
//
//

#include "CPathManager.h"
#include "CPath.h"
#include <vector>

using namespace std;

IMPLEMENT_SINGLETON(CPathManager);


CPathManager::CPathManager()
: paths_(NULL)
{
    
}



CPathManager::~CPathManager()
{
    setPaths(NULL);
}



bool CPathManager::initialize()
{
    do
    {
        setPaths(CCDictionary::create());
        CC_BREAK_IF(!paths_);
        
        const char* cp = "game_path.pmp";
        const char* fcp = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(cp);
        
        FILE* fp = fopen(fcp, "rb");
        CC_BREAK_IF(NULL == fp);
        int32_t pathCount;
        fread(&pathCount, sizeof(pathCount), 1, fp);
        vector<int32_t> offsetTable;
        vector<int32_t> lengthTable;
        int32_t offset, length;
        for (int32_t i = 0; i < pathCount; ++i)
        {
            fread(&offset, sizeof(int32_t), 1, fp);
            fread(&length, sizeof(int32_t), 1, fp);
            offsetTable.push_back(offset);
            lengthTable.push_back(length);
        }
        for (int32_t i = 0; i < pathCount; ++i)
        {
            offset = offsetTable[i];
            length = lengthTable[i];
            
            auto_ptr<char> pathData(new char[length]);
            fseek(fp, offset, SEEK_SET);
            fread(pathData.get(), length, 1, fp);
            
            CPath* path = new CPath;
            path->autorelease();
            CC_BREAK_IF(!path->initWithData(pathData.get(), length));

            paths_->setObject(path, path->getPathName());
        }

        return true;
    }while (false);
        
    return false;
}



CPath* CPathManager::getPathByName(const string& name)
{
    return dynamic_cast<CPath*>(paths_->objectForKey(name));
}
