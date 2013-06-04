//
//  CCDictionarySaver.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-4-24.
//
//

#include "CCDictionarySaver.h"
#include <libxml/parser.h>
#include <libxml/tree.h>

#define ROOT_NODE_NAME BAD_CAST("plist")
#define ROOT_PLIST_PROP BAD_CAST("version")
#define ROOT_PLIST_VERSION BAD_CAST("1.0")
#define DICT_NODE_DICT BAD_CAST("dict")
#define DICT_NODE_KEY BAD_CAST("key")
#define DICT_NODE_ARRAY BAD_CAST("array")
#define DICT_NODE_STRING BAD_CAST("string")

bool CCDictionarySaver::save2Plist(CCDictionary* pDict, const char* filename)
{
    do
    {
        xmlDocPtr xmlDoc = xmlNewDoc(BAD_CAST"1.0");
        CC_BREAK_IF(!xmlDoc);
        CC_BREAK_IF(!pDict);
        CC_BREAK_IF(!filename);
        
        xmlNodePtr root = xmlNewNode(NULL, ROOT_NODE_NAME);
        CC_BREAK_IF(!root);
        
        xmlNewProp(root, ROOT_PLIST_PROP, ROOT_PLIST_VERSION);
        
        CC_BREAK_IF(!saveDictionary(pDict, root));
        
        // not sure how to check the return value
        xmlDocSetRootElement(xmlDoc, root);
        
        CC_BREAK_IF(!xmlSaveFile(filename, xmlDoc));
        
        xmlFreeDoc(xmlDoc);
        return true;
    } while (false);
    
    return false;
}



bool CCDictionarySaver::saveArray(CCArray* pArray, xmlNodePtr node)
{
    do
    {
        xmlNodePtr array_node = xmlNewNode(NULL, DICT_NODE_ARRAY);
        CC_BREAK_IF(!array_node);
        
        CC_BREAK_IF(!xmlAddChild(node, array_node));
        
        CCObject* obj;
        CCARRAY_FOREACH(pArray, obj)
        {
            if (dynamic_cast<CCString*>(obj))
            {
                CCString* s = dynamic_cast<CCString*>(obj);
                CC_BREAK_IF(!saveString(s->getCString(), array_node));
            }
            else if (dynamic_cast<CCDictionary*>(obj))
            {
                CC_BREAK_IF(!saveDictionary(dynamic_cast<CCDictionary*>(obj), array_node));
            }
            else if (dynamic_cast<CCArray*>(obj))
            {
                CC_BREAK_IF(!saveArray(dynamic_cast<CCArray*>(obj), array_node));
            }
        }
        return true;
    } while (false);
    
    return false;
}



bool CCDictionarySaver::saveDictionary(CCDictionary* pDict, xmlNodePtr node)
{
    do
    {
        xmlNodePtr dict_node = xmlNewNode(NULL, DICT_NODE_DICT);
        CC_BREAK_IF(!dict_node);
        
        CC_BREAK_IF(!xmlAddChild(node, dict_node));
        
        CCDictElement* pElem;
        CCDICT_FOREACH(pDict, pElem)
        {
            saveKey(pElem->getStrKey(), dict_node);
            
            CCObject* obj = pElem->getObject();

            if (dynamic_cast<CCString*>(obj))
            {
                CCString* s = dynamic_cast<CCString*>(obj);
                CC_BREAK_IF(!saveString(s->getCString(), dict_node));
            }
            else if (dynamic_cast<CCDictionary*>(obj))
            {
                CC_BREAK_IF(!saveDictionary(dynamic_cast<CCDictionary*>(obj), dict_node));
            }
            else if (dynamic_cast<CCArray*>(obj))
            {
                CC_BREAK_IF(!saveArray(dynamic_cast<CCArray*>(obj), dict_node));
            }
        }
        return true;
    } while (false);
    
    return false;
}



bool CCDictionarySaver::saveKey(const char* key, xmlNodePtr node)
{
    do
    {
        xmlNodePtr tmpNode = xmlNewNode(NULL, DICT_NODE_KEY);
        xmlNodePtr content = xmlNewText(BAD_CAST key);
        CC_BREAK_IF(!tmpNode);
        CC_BREAK_IF(!content);
        CC_BREAK_IF(!xmlAddChild(node, tmpNode));
        CC_BREAK_IF(!xmlAddChild(tmpNode, content));
        return true;
    } while (false);
    
    return false;
}



bool CCDictionarySaver::saveString(const char* str, xmlNodePtr node)
{
    do
    {
        xmlNodePtr tmpNode = xmlNewNode(NULL, DICT_NODE_STRING);
        xmlNodePtr content = xmlNewText(BAD_CAST str);
        CC_BREAK_IF(!tmpNode);
        CC_BREAK_IF(!content);
        CC_BREAK_IF(!xmlAddChild(node, tmpNode));
        CC_BREAK_IF(!xmlAddChild(tmpNode, content));
        return true;
    } while (false);
    
    return false;
}
