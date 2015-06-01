//
//  BaseCode.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef SwampAttack_BaseCode_h
#define SwampAttack_BaseCode_h

#include "cocos2d.h"

USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

//-------------
extern  Size    winSize;
extern  Size    visibleSize;
extern  Vec2    visibleOrigin;


// get GameDirector


//------------
#define ImagePath( name ) std::string("image/")+std::string( name )
#define MusicPath( name ) (std::string("music/")+std::string( name ))
#define ConfigePath( name ) std::string("config/")+std::string( name )+std::string(".csv")
//-------------
#define CREATE_SCENE_FUNC(__TYPE__) \
static cocos2d::Scene * scene() \
{ \
    Scene * scene = Scene::create(); \
    Layer * layer = __TYPE__::create(); \
    scene->addChild(layer); \
    return scene; \
}

#endif


