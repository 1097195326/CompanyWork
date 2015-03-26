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


Size visibleSize = Director::getInstance()->getVisibleSize();
Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

Size winSize = Director::getInstance()->getWinSize();


#define CREATE_SCENE_FUNC(__TYPE__) \
static cocos2d::Scene * scene() \
{ \
    cocos2d::Scene * scene = cocos2d::Scene::create(); \
    cocos2d::Layer * layer = __TYPE__::create(); \
    scene->addChild(layer); \
    return scene; \
}

#endif
