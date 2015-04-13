//
//  GameFightScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "GameFightScene.h"
#include "EnemySprite.h"
#include "cocostudio/CocoStudio.h"

#include "CCCsvHelper.h"
#include "GameLoading.h"


using namespace cocostudio;

bool GameFightScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    GameLoading::loadFrames();
    
    Sprite * bgSprite = Sprite::create(ImagePath("bg.png"));
    addChild(bgSprite);
    bgSprite->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5));
    
//    EnemySprite * sprite =EnemySprite::create();
//    sprite->createActionsWithFileName("stone_hurt");
//    sprite->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5,
//                              visibleOrigin.y + visibleSize.height * 0.5)
//                        );
//    addChild(sprite);
//    sprite->move();
    
//    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("image/skeleton.json", this, CC_SCHEDULE_SELECTOR(TestAsynchronousLoading::dataLoaded));
    
//    ArmatureDataManager::getInstance()->addArmatureFileInfo("image/Cowboy.ExportJson");
////    ArmatureDataManager::getInstance()->addArmatureFileInfoAsync("image/skeleton.json", this, nullptr);
//    Armature *armature = Armature::create("Cowboy");
//    armature->getAnimation()->playWithIndex(0);
//    armature->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5,
//                                visibleOrigin.y + visibleSize.height * 0.5));
//    addChild(armature);
    
//    GCCsvHelper * csvHelper2 = new GCCsvHelper("guanqia.csv");
    return true;
}
