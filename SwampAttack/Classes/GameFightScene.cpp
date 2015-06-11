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

#include "GameMapScene.h"

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
    g_f_layer = NULL;
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
    
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);

    m_listener->onTouchBegan = CC_CALLBACK_2(GameFightScene::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(GameFightScene::touchMoved, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(GameFightScene::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    MenuItemImage * pauseButton = MenuItemImage::create(ImagePath("fight_pause_button.png"),
                                                        ImagePath("fight_pause_button.png"),
                                                        CC_CALLBACK_1( GameFightScene::pauseGame, this));
    pauseButton->setPosition(m_visibleOrigin.x + pauseButton->getContentSize().width * 0.6,
                             m_visibleOrigin.y + m_visibleSize.height - pauseButton->getContentSize().height * 0.6);
    Menu * buttonMenu = Menu::create(pauseButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,2);
    
    log("fight scene init");
    _G_D->initGameView();
    
    _G_D->startGame();
    
    
    return true;
}
void GameFightScene::pauseGame(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    RenderTexture * rt = RenderTexture::create(m_visibleSize.width, m_visibleSize.height);
    
    rt->begin();
    this->visit();
    rt->end();
    _G_D->stopGame();
    GamePauseScene * pauseScene = new GamePauseScene(rt);
    pauseScene->autorelease();
    addChild(pauseScene,10);
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
