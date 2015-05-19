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
#include "GameDirector.h"
#include "GameMapManager.h"

//---
#include "EnemyManager.h"
#include "ConfigManager.h"
#include "GuanQiaModel.h"
#include "BaseUtil.h"
#include "HumanSprite.h"
#include "ProgressBar.h"
#include "Human.h"




bool GameFightScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    GameDirector * gameDirector = _G_D;
    gameDirector->setGameLayer(this);
    addChild(gameDirector);
    
    
    GameLoading::loadFrames();
    
    gameDirector->initGameSingle();
    
    Sprite * bgSprite = Sprite::create(ImagePath("scene1_Bg.png"));
    addChild(bgSprite);
    bgSprite->setPosition(Vec2(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5));
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event){
        GameFightScene * gameFightScene = static_cast<GameFightScene *>(event->getCurrentTarget());
        gameFightScene->touchBegan(touch, event);
        return true;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event){
        GameFightScene * gameFightScene = static_cast<GameFightScene *>(event->getCurrentTarget());
        gameFightScene->touchMoved(touch, event);
    };
    listener->onTouchEnded = [](Touch* touch, Event* event){
        GameFightScene * gameFightScene = static_cast<GameFightScene *>(event->getCurrentTarget());
        gameFightScene->touchEnd(touch, event);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    Json::Value value = _C_M->getDataByTag("guanqia", "400001");
    GuanqiaModel * guanQia = new GuanqiaModel(value);
    EnemyManager::getInstance()->setData(guanQia->getMonsters());
    
    
    
    return true;
}
bool GameFightScene::touchBegan(Touch *touch, Event *event)
{
    _G_D->onTouchBegin(touch, event);
    return true;
}
void GameFightScene::touchMoved(Touch *touch, Event *event)
{
    _G_D->onTouchMove(touch, event);
}
void GameFightScene::touchEnd(Touch *touch, Event *event)
{
    _G_D->onTouchEnd(touch, event);
}
