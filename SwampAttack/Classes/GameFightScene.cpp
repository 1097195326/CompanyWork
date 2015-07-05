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
#include "GuanQiaManager.h"
#include "GamePauseScene.h"

#include "GameMapScene.h"
#include "GameOverScene.h"
#include "GameReliveLayer.h"
//---
//#include "EnemyManager.h"
//#include "ConfigManager.h"
//#include "GuanQiaModel.h"
//#include "BaseUtil.h"
//#include "HumanSprite.h"
//#include "ProgressBar.h"
//#include "Human.h"

GameFightScene * g_f_layer = NULL;

Scene * GameFightScene::scene()
{
    Scene * scene = Scene::create();
    GameFightScene * layer =new GameFightScene();
    layer->init();
    layer->autorelease();
    scene->addChild(layer);
    return scene;
}
GameFightScene * GameFightScene::getInstance()
{
    return g_f_layer;
}
GameFightScene::GameFightScene()
{
    
}
GameFightScene::~GameFightScene()
{
//    g_f_layer = NULL;
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
bool GameFightScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    g_f_layer = this;
    
    Sprite * bgSprite = Sprite::create(ImagePath("scene1_Bg.png"));
    addChild(bgSprite);
    bgSprite->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                               m_visibleOrigin.y + m_visibleSize.height * 0.5));
    
    Sprite * fgSprite = Sprite::create(ImagePath("scene1_Fg.png"));
    addChild(fgSprite,640);
    fgSprite->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                               m_visibleOrigin.y + fgSprite->getContentSize().height * 0.5));
    
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);

    m_listener->onTouchBegan = CC_CALLBACK_2(GameFightScene::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(GameFightScene::touchMoved, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(GameFightScene::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    MenuItemImage * pauseButton = MenuItemImage::create(ImagePath("fight_pause_button.png"),
                                                        ImagePath("fight_pause_button.png"),
                                                        CC_CALLBACK_1( GameFightScene::pauseGame, this));
    pauseButton->setPosition(m_visibleOrigin.x + pauseButton->getContentSize().width * 0.5,
                             m_visibleOrigin.y + m_visibleSize.height
                             - pauseButton->getContentSize().height * 0.6);
    Menu * buttonMenu = Menu::create(pauseButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,2);
    
    m_goldNumLabel = Label::createWithTTF(StringUtils::format("%d",_G_D->getGoldNum()),
                                          "fonts/Arial Black.ttf",
                                          20);
    m_goldNumLabel->setPosition(_G_M_M->fightScene_Gold_Position);
    m_goldNumLabel->enableOutline(Color4B(0, 0, 0, 255),2);
    addChild(m_goldNumLabel);
    
    Sprite * goldIcon = Sprite::create(ImagePath("jinbi_icon.png"));
    goldIcon->setPosition(_G_M_M->fightScene_Gold_Position + Vec2(50, 0));
    goldIcon->setScale(0.7);
    addChild(goldIcon);
    
    string guanqiaName = GuanQiaManager::getInstance()->getCurrentGuanqia()->getGuanqiaName();
    Label * showLabel = Label::createWithTTF(guanqiaName, "fonts/mimi.ttf", 40);
    showLabel->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                           m_visibleOrigin.y + m_visibleSize.height * 0.7);
    addChild(showLabel);
    showLabel->runAction(Sequence::create(DelayTime::create(3),
                                          FadeOut::create(0.3),
                                          NULL));
    
//    log("fight scene init");
    _G_D->initGameView();
    
    _G_D->startGame();
    setSubject(_G_D);
    
    
    return true;
}
void GameFightScene::updateData()
{
    m_goldNumLabel->setString(StringUtils::format("%d",_G_D->getGoldNum()));
    if (_G_D->isOver())
    {
        log("game is over");
        _G_D->stopGame();
        shopGameActions();
        
        
        if (_G_D->getOverStatus() == o_win)
        {
            showOverLayer();
        }else
        {
            RenderTexture * rt = getFightSceneTex();
            GameReliveLayer * reliveLayer = new GameReliveLayer(rt);
            reliveLayer->setFightLayer(this);
            reliveLayer->autorelease();
            addChild(reliveLayer,640);
        }
    }
}
void GameFightScene::shopGameActions()
{
    m_actions = Director::getInstance()->getActionManager()->pauseAllRunningActions();
}
void GameFightScene::resumeGameActions()
{
    Director::getInstance()->getActionManager()->resumeTargets(m_actions);
}
void GameFightScene::showOverLayer()
{
    RenderTexture * rt = getFightSceneTex();
    GameOverScene * overScene = new GameOverScene(_G_D->getOverStatus(),rt);
    overScene->init();
    overScene->autorelease();
    addChild(overScene,640);
}
RenderTexture * GameFightScene::getFightSceneTex()
{
    RenderTexture * rt = RenderTexture::create(m_visibleSize.width, m_visibleSize.height);
    rt->begin();
    this->visit();
    rt->end();
    return rt;
}
void GameFightScene::pauseGame(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    shopGameActions();
    _G_D->stopGame();
    RenderTexture * rt = getFightSceneTex();
    GamePauseScene * pauseScene = new GamePauseScene(rt);
    pauseScene->autorelease();
    pauseScene->setFightLayer(this);
    addChild(pauseScene,640);
}
void GameFightScene::addBulletTexiao(cocos2d::Vec2 position)
{
    Sprite * tx = Sprite::create();
    tx->setPosition(position);
    addChild(tx,640);
    ActionInterval * ac = BaseUtil::makeAnimateWithNameAndIndex("bullet_hit", 6);
    tx->runAction(Sequence::create(ac,
                                   CallFuncN::create(CC_CALLBACK_1(GameFightScene::removeBulletTexiao, this)),
                                   NULL));
    
}
void GameFightScene::removeBulletTexiao(cocos2d::Node *pSender)
{
    Sprite * sp = (Sprite *)pSender;
    sp->stopAllActions();
    sp->removeFromParentAndCleanup(true);
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
