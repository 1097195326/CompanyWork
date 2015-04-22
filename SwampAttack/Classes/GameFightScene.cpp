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

//---
#include "EnemyManager.h"
#include "ConfigManager.h"
#include "GuanQiaModel.h"
#include "BaseUtil.h"
#include "HumanSprite.h"
#include "ProgressBar.h"
#include "Human.h"



using namespace cocostudio;


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
    
    Sprite * bgSprite = Sprite::create(ImagePath("bg.png"));
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
    
    
    Json::Value value = _C_M->getDataByTag("guanqia", "300001");
    GuanqiaModel * guanQia = new GuanqiaModel(value);
    EnemyManager::getInstance()->setData(guanQia->getMonsters());
    
    Human::getInstance();
    
//    ProgressTimer * pt = ProgressTimer::create(Sprite::create(ImagePath("xuenei.png")));
//    pt->setPosition(Vec2(200, 100));
//    pt->setType(ProgressTimer::Type::BAR);
//    pt->setBarChangeRate(Vec2(1, 0));
//    pt->setMidpoint(Vec2(1, 0));
//    addChild(pt,5);
//    pt->setPercentage(70);
//    pt->runAction(ProgressTo::create(2, 100));
    
//    ProgressBar *  p = new ProgressBar("xuenei.png","xuewai.png");
//    p->setPosition(Vec2(200, 200));
//    addChild(p);
//    p->updatePercent(100);
    Sprite  * s = Sprite::create("CloseSelected.png");
    s->setPosition(Vec2(200, 200));
    addChild(s);
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
