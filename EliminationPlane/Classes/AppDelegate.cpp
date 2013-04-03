//
//  TheForceAppDelegate.cpp
//  TheForce
//
//  Created by Ming Zhao on 2/1/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "Common.h"
#include "TFGameObjectManager.h"
#include "TFBattleFieldLayer.h"
#include "TFTexturesCache.h"
#include "TFObjectFactory.h"

#include "TFRole.h"

#include <time.h>

USING_NS_CC;

AppDelegate::AppDelegate()
{
    time_t t;
    srand((unsigned) time(&t));
}

AppDelegate::~AppDelegate()
{

}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    this->setupConfigurationFiles();
    
    this->setupMultipleResolutionSupport();
    
    // create a scene. it's an autorelease object
    if (!OBJECT_FACTORY->Initialize())
    {
        __CCLOGWITHFUNCTION("TFObjectFactory initialize failed");
        return false;
    }

    if (!GAME_OJBECT_MANAGER->init())
    {
        return false;
    }
    
    BATTLE_FIELD_LAYER->init();
    CCScene *scene = CCScene::create();
    scene->addChild(BATTLE_FIELD_LAYER);
    pDirector->runWithScene(scene);

    return true;
}



// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}



// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}



void AppDelegate::setupConfigurationFiles()
{
    const char* udFileName = "GameSettings.plist";
	const char* udBundleFilePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(udFileName);

    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("_IS_EXISTED", false))
    {
        CCDictionary* dict = CCDictionary::createWithContentsOfFile(udBundleFilePath);
        for (int i = 0; i < GAME_SETTINGS_MAX; i++)
        {
            const CCString* value = dict->valueForKey(GAME_SETTINGS_TEXT(i));
            SaveStringToUserDefault(i, value->getCString());
        }
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("_IS_EXISTED", true);
        
        FlushUserDefault;
    }
}


void AppDelegate::setupMultipleResolutionSupport()
{
    typedef struct tagResource
    {
        CCSize sizeInPixel;
        CCSize sizeDesign;
        char suffix[100];
    } Resource;
    
    Resource resPhone  =  { CCSizeMake(480, 320), CCSizeMake(480, 320), "" };
    Resource resPhoneRetina35 =  { CCSizeMake(960, 640), CCSizeMake(480, 320), "-hd" };
    Resource resPhoneRetina40 =  { CCSizeMake(1136, 640), CCSizeMake(568, 320), "-hd" };
    Resource resTable =  { CCSizeMake(1024, 768), CCSizeMake(1024, 768), "-ipad" };
    Resource resTableRetina  =  { CCSizeMake(2048, 1536), CCSizeMake(1024, 768), "-ipadhd" };
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    // multiple resolution support
    CCSize frameSize = pEGLView->getFrameSize();
    Resource actualResource;
    float actualWidth = max(frameSize.width, frameSize.height);
    
    if (actualWidth > resPhoneRetina40.sizeInPixel.width)
    {
        actualResource = resTableRetina;
    }
    else if (actualWidth > resTable.sizeInPixel.width)
    {
        actualResource = resPhoneRetina40;
    }
    else if (actualWidth > resPhoneRetina35.sizeInPixel.width)
    {
        actualResource = resTable;
    }
    else if (actualWidth > resPhone.sizeInPixel.width)
    {
        actualResource = resPhoneRetina35;
    }
    else
    {
        actualResource = resPhone;
    }
    
    //    CCFileUtils::sharedFileUtils()->setResourceDirectory(actualResource.directory);
    
    // Set the design resolution
    if (frameSize.width > frameSize.height) {
        pEGLView->setDesignResolutionSize(actualResource.sizeDesign.width, actualResource.sizeDesign.height, kResolutionNoBorder);
    }
    else
    {
        pEGLView->setDesignResolutionSize(actualResource.sizeDesign.height, actualResource.sizeDesign.width, kResolutionNoBorder);
    }
    
    pDirector->setContentScaleFactor(actualResource.sizeInPixel.height / actualResource.sizeDesign.height);
    
    // set texture resoures
    TEXTURE_CACHE->addTextures(actualResource.suffix);
}


