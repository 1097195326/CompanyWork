//
//  GameOverScene.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/6/1.
//
//

#include "GameOverScene.h"
#include "GameMapScene.h"
#include "GameLoadingScene.h"

#include "GuanQiaManager.h"
#include "GunManager.h"
#include "PropManager.h"
#include "GunManager.h"

//#include "GameDirector.h"
//#include "EnemyManager.h"
//#include "GameLoading.h"


Scene * GameOverScene::scene(GameOverStatus status,RenderTexture * rt)
{
    Scene * scene = Scene::create();
    GameOverScene * layer = new GameOverScene(status,rt);
    layer->autorelease();
    layer->init();
    scene->addChild(layer,1);
    
    return scene;
}
GameOverScene::GameOverScene(GameOverStatus status, RenderTexture * rt)
{
    m_overStatus = status;
    
    Sprite * scenebg = Sprite::createWithTexture(rt->getSprite()->getTexture());
    scenebg->setPosition(m_visibleSize.width * 0.5,m_visibleSize.height * 0.5);
    scenebg->setFlippedY(true);
    scenebg->setColor(Color3B::GRAY);
    addChild(scenebg);
}
GameOverScene::~GameOverScene()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameOverScene::touchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    
    Sprite * bg = Sprite::create(ImagePath("overScene_bg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg);
    
    
    
    int widthOffset = 100;
    MenuItemImage * gotoMapButton = MenuItemImage::create(ImagePath("overScene_tomap.png"),
                                                       ImagePath("overScene_tomap.png"),
                                                       CC_CALLBACK_1( GameOverScene::gotoMap, this));
    MenuItemImage * restartButton = MenuItemImage::create(ImagePath("overScene_restart.png"),
                                                          ImagePath("overScene_restart.png"),
                                                          CC_CALLBACK_1( GameOverScene::restartGame, this));
    Menu * buttonMenu = NULL;
    if (m_overStatus == o_win)
    {
        Sprite * title = Sprite::create(ImagePath("overScene_win.png"));
        title->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                           m_visibleOrigin.y + m_visibleSize.height * 0.58);
        addChild(title);
        MenuItemImage * nextButton = MenuItemImage::create(ImagePath("overScene_next.png"),
                                                           ImagePath("overScene_next.png"),
                                                           CC_CALLBACK_1( GameOverScene::nextGuanqia, this));
        gotoMapButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 - widthOffset,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.22);
        restartButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.22);
        nextButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 + widthOffset,
                                m_visibleOrigin.y + m_visibleSize.height * 0.22);
        buttonMenu = Menu::create(gotoMapButton,restartButton,nextButton, NULL);
        
        GuanqiaModel * curGuanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
        GuanqiaModel * nextGuanqia = GuanQiaManager::getInstance()->getGuanqiaById(curGuanqia->getUnlockMission());
        nextGuanqia->unlockGuanqia();
        GunManager::getInstance()->checkUnlock();
        PropManager::getInstance()->checkUnlock();
        GunManager::getInstance()->saveBullet();
    }else
    {
        Sprite * title = Sprite::create(ImagePath("overScene_title.png"));
        title->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                           m_visibleOrigin.y + m_visibleSize.height * 0.58);
        addChild(title);
        gotoMapButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 - widthOffset * 0.7,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.22);
        restartButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 + widthOffset * 0.7,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.22);
        buttonMenu = Menu::create(gotoMapButton,restartButton, NULL);
    }
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,200);
    
    
    return true;
}
void GameOverScene::restartGame(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    GuanqiaModel * guanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
    Director::getInstance()->replaceScene(GameLoadingScene::scene(guanqia->getId()));
}
void GameOverScene::gotoMap(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameMapScene::scene());
}
void GameOverScene::nextGuanqia(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    GuanqiaModel * curGuanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
    GuanqiaModel * nextGuanqia = GuanQiaManager::getInstance()->getGuanqiaById(curGuanqia->getUnlockMission());
    Director::getInstance()->replaceScene(GameLoadingScene::scene(nextGuanqia->getId()));
}
bool GameOverScene::touchBegan(Touch *touch, Event *event)
{
    return true;
}