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
#include "GamePauseScene.h"

//---
//#include "EnemyManager.h"
//#include "ConfigManager.h"
//#include "GuanQiaModel.h"
//#include "BaseUtil.h"
//#include "HumanSprite.h"
//#include "ProgressBar.h"
//#include "Human.h"


Scene * GameFightScene::scene()
{
    Scene * scene = Scene::create();
    GameFightScene * layer =(GameFightScene*)GameFightScene::getInstance();
    layer->init();
    scene->addChild(layer);
    
    return scene;
}
Layer * GameFightScene::getInstance()
{
    static GameFightScene layer;
    return &layer;
}
bool GameFightScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
//    GameLoading::loadFrames();
    _G_D->initGameSingle();
    
    Sprite * bgSprite = Sprite::create(ImagePath("scene1_Bg.png"));
    addChild(bgSprite);
    bgSprite->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                               m_visibleOrigin.y + m_visibleSize.height * 0.5));
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(GameFightScene::touchBegan, this);
//    [](Touch* touch, Event* event){
//        GameFightScene * gameFightScene = static_cast<GameFightScene *>(event->getCurrentTarget());
//        gameFightScene->touchBegan(touch, event);
//        return true;
//    };
    listener->onTouchMoved = CC_CALLBACK_2(GameFightScene::touchMoved, this);
//    [](Touch* touch, Event* event){
//        GameFightScene * gameFightScene = static_cast<GameFightScene *>(event->getCurrentTarget());
//        gameFightScene->touchMoved(touch, event);
//    };
    listener->onTouchEnded = CC_CALLBACK_2(GameFightScene::touchEnd, this);
//    [](Touch* touch, Event* event){
//        GameFightScene * gameFightScene = static_cast<GameFightScene *>(event->getCurrentTarget());
//        gameFightScene->touchEnd(touch, event);
//    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
//    Json::Value value = _C_M->getDataByTag("guanqia", "400001");
//    GuanqiaModel * guanQia = new GuanqiaModel(value);
//    EnemyManager::getInstance()->setData(guanQia->getMonsters());
    
    MenuItemImage * pauseButton = MenuItemImage::create(ImagePath("fight_pause_button.png"),
                                                        ImagePath("fight_pause_button.png"),
                                                        CC_CALLBACK_1( GameFightScene::pauseGame, this));
    pauseButton->setPosition(m_visibleOrigin.x + pauseButton->getContentSize().width * 0.6,
                             m_visibleOrigin.y + m_visibleSize.height - pauseButton->getContentSize().height * 0.6);
    Menu * buttonMenu = Menu::create(pauseButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,200);
    
    _G_D->startGame();
    
//    log("game fight scene init");
    
    return true;
}
void GameFightScene::pauseGame(cocos2d::Ref *pSender)
{
    RenderTexture * rt = RenderTexture::create(m_visibleSize.width, m_visibleSize.height);
    
    rt->begin();
    this->visit();
    rt->end();
    _G_D->stopGame();
    Director::getInstance()->pushScene(GamePauseScene::scene(rt));
    
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
