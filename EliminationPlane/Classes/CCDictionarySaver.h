//
//  CCDictionarySaver.h
//  EliminationPlane
//
//  Created by 马 俊 on 13-4-24.
//
//

#ifndef __EliminationPlane__CCDictionarySaver__
#define __EliminationPlane__CCDictionarySaver__

#include "cocos2d.h"
#include <libxml/tree.h>

USING_NS_CC;

// USAGE:
// string filename = cocos2d::CCFileUtils::sharedFileUtils()->getWriteablePath() + string("test.plist");
// CCDictionarySaver::save2Plist(pDictToSave, filename.c_str());

class CCDictionarySaver
{
public:
    static bool save2Plist(CCDictionary* pDict, const char* filename);
protected:
    static bool saveArray(CCArray* pArray, xmlNodePtr node);
    static bool saveDictionary(CCDictionary* pDict, xmlNodePtr node);
    static bool saveKey(const char* key, xmlNodePtr node);
    static bool saveString(const char* str, xmlNodePtr node);
private:
};

#endif /* defined(__EliminationPlane__CCDictionarySaver__) */
