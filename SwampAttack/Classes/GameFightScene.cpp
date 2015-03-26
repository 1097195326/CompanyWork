//
//  GameFightScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "GameFightScene.h"



bool GameFightScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto animationCache = AnimationCache::getInstance();
    animationCache->addAnimationsWithFile("boom.plist");
    
    return true;
}