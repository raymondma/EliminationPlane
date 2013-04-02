//
//  Common.h
//  TheForce
//
//  Created by Ming Zhao on 2/11/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#ifndef TheForce_Common_h
#define TheForce_Common_h

#pragma mark - Math

#define FLT_EQUAL(x, y) (fabsf((x) - (y)) < FLT_EPSILON)
#define FLT_LE(x, y)    ((x) < (y) || fabsf((x) - (y)) < FLT_EPSILON)
#define FLT_GE(x, y)    ((x) > (y) || fabsf((x) - (y)) < FLT_EPSILON)

#pragma mark - Colors

#define COLOR4B_TRANSPARENT         (ccc4(0, 0, 0, 0))
#define COLOR4B_DARK_TRANSPARENT    (ccc4(0, 0, 0, 220))

#pragma mark - Notifications

//#define NOTIFICATION_TRANSIT_MESSAGE        "NotificationTransitMessage"

#pragma mark - Textures

enum GameArts
{
    GA_ACTORS = 0,
    GA_BULLETS,
    GA_SCENES,
    GAME_ARTS_MAX
};
#define GAME_ARTS_TEXT(val) ((string[]) {"ga_actors", \
                                         "ga_bullets", \
                                         "ga_scenes", \
                                         "", \
                                        }[(val)])

enum GameFonts
{
    GAME_FONTS_MESSAGE = 0,
    GAME_FONTS_MAX
};


#define GAME_FONTS_TEXT(val)    ((string[]) {"yahei", \
                                             "", \
                                            }[(val)])



#pragma mark - User defaults

enum GameSettings
{
    GAME_SETTINGS_NULL = 0,
    GAME_SETTINGS_MAX,
};
#define GAME_SETTINGS_TEXT(val)  ((string[]) {"GAME_SETTINGS_NULL", \
                                              "", \
                                             }[(val)])

#define SaveStringToUserDefault(key, value) \
        CCUserDefault::sharedUserDefault()->setStringForKey(GAME_SETTINGS_TEXT((key)).c_str(), (value))
#define SaveIntegerToUserDefault(key, value) \
        CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_SETTINGS_TEXT((key)).c_str(), (value))
#define SaveBooleanToUserDefault(key, value) \
        CCUserDefault::sharedUserDefault()->setBoolForKey(GAME_SETTINGS_TEXT((key)).c_str(), (value))
#define LoadStringFromUserDefault(key, dVal) \
        CCUserDefault::sharedUserDefault()->getStringForKey(GAME_SETTINGS_TEXT((key)).c_str(), (dVal))
#define LoadIntegerFromUserDefault(key, dVal) \
        CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_SETTINGS_TEXT((key)).c_str(), (dVal))
#define LoadBooleanFromUserDefault(key, dVal) \
        CCUserDefault::sharedUserDefault()->getBoolForKey(GAME_SETTINGS_TEXT((key)).c_str(), (dVal))
#define FlushUserDefault      CCUserDefault::sharedUserDefault()->flush()

#endif
