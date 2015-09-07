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
    
    int sceneIndex = GuanQiaManager::getInstance()->getCurrentSceneIndex();
    
    std::string bgName = StringUtils::format("scene%d_Bg.png",sceneIndex);
    std::string fgName = StringUtils::format("scene%d_Fg.png",sceneIndex);
    
    m_bgSprite = Sprite::create(ImagePath(bgName));
    addChild(m_bgSprite);
    m_bgSprite->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                               m_visibleOrigin.y + m_visibleSize.height * 0.5));
    
    Sprite * fgSprite = Sprite::create(ImagePath(fgName));
    if (fgSprite) {
        addChild(fgSprite,640);
        fgSprite->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                   m_visibleOrigin.y + fgSprite->getContentSize().height * 0.5));
    }
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);

    m_listener->onTouchBegan = CC_CALLBACK_2(GameFightScene::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(GameFightScene::touchMoved, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(GameFightScene::touchEnd, this);
    m_listener->onTouchCancelled = CC_CALLBACK_2(GameFightScene::touchCancelled, this);
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
    
    LayerColor * heiLayer = LayerColor::create(Color4B(0, 0, 0, 180));
    addChild(heiLayer,700);
    heiLayer->runAction(Sequence::create(DelayTime::create(2),
                                         FadeOut::create(0.3f),
                                         CallFuncN::create(CC_CALLBACK_1(GameFightScene::removeBulletTexiao, this)),
                                         NULL));
    
    string guanqiaName = GuanQiaManager::getInstance()->getCurrentGuanqia()->getGuanqiaName();
    Label * showLabel = Label::createWithTTF(guanqiaName, "fonts/mimi.ttf", 100);
    showLabel->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                           m_visibleOrigin.y + m_visibleSize.height * 0.55);
    addChild(showLabel,700);
    showLabel->runAction(Sequence::create(DelayTime::create(2),
                                          FadeOut::create(0.3),
                                          CallFuncN::create(CC_CALLBACK_1(GameFightScene::removeBulletTexiao, this)),
                                          NULL));
//    log("fight scene init");
    _G_D->initGameView();
    
    Sprite * cheDeng = Sprite::create(ImagePath("house_deng.png"));
    cheDeng->setPosition(_G_M_M->fightScene_HouseDeng_Position);
    addChild(cheDeng,4);
    
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
            SimpleAudioEngine::getInstance()->playEffect(MusicPath("gameWin.mp3").c_str());
            showOverLayer();
        }else
        {
            SimpleAudioEngine::getInstance()->playEffect(MusicPath("gamelose.mp3").c_str());
            RenderTexture * rt = getFightSceneTex();
            GameReliveLayer * reliveLayer = new GameReliveLayer(rt);
            reliveLayer->setFightLayer(this);
            reliveLayer->autorelease();
            addChild(reliveLayer,642);
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
    addChild(overScene,642);
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
    addChild(pauseScene,642);
}
void GameFightScene::addBulletTexiao(cocos2d::Vec2 position, std::string name, int frames)
{
    Sprite * tx = Sprite::create();
    tx->setPosition(position);
    addChild(tx,640);
    ActionInterval * ac = BaseUtil::makeAnimateWithNameAndIndex(name, frames);
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
void GameFightScene::touchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    _G_D->onTouchEnd(touch, event);
}
void GameFightScene::zhenPingUpDown()
{
    ActionInterval * s1 = ScaleTo::create(0.05f, 1.02);
    ActionInterval * s2 = ScaleTo::create(0.05f, 1);
    ActionInterval * m1 = MoveBy::create(0.05f, Vec2(10, -20));
    ActionInterval * m2 = MoveBy::create(0.05f, Vec2(0, 40));
    ActionInterval * m3 = MoveBy::create(0.05f, Vec2(-20, -40));
    ActionInterval * m4 = MoveBy::create(0.05f, Vec2(0, 40));
    ActionInterval * m5 = MoveBy::create(0.05f, Vec2(10, -20));
    
    m_bgSprite->runAction(Sequence::create(Spawn::create(m1,s1, NULL),
                                           m2,
                                           m3,
                                           m4,
                                           Spawn::create(m5,s2, NULL),
                                           NULL));
}
void GameFightScene::shanBai()
{
    LayerColor * baiLayer = LayerColor::create(Color4B(255, 255, 255, 255));
    addChild(baiLayer,660);
    baiLayer->runAction(Sequence::create(FadeIn::create(0.05f),
                                         FadeOut::create(0.05f),
                                         CallFuncN::create(CC_CALLBACK_1(GameFightScene::removeBulletTexiao, this)),
                                         NULL));
}