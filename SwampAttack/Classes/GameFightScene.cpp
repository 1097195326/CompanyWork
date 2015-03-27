//
//  GameFightScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "GameFightScene.h"
#include "EnemySprite.h"


bool GameFightScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
//    EnemySprite * sprite =new EnemySprite();
    EnemySprite * sprite =EnemySprite::create();
    sprite->createActionsWithFileName("stone_hurt");
    sprite->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5,
                              visibleOrigin.y + visibleSize.height * 0.5)
                        );
    addChild(sprite);
//    sprite->autorelease();
    sprite->walk();
    
    return true;
}