//
//  GameOverScene.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/6/1.
//
//

#include "GameOverScene.h"
#include "GameMapScene.h"
#include "GameShopScene.h"
#include "GameLoadingScene.h"

#include "GuanQiaManager.h"
#include "GunManager.h"
#include "PropManager.h"
#include "GunManager.h"

#include "GameDirector.h"
#include "GameUser.h"

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
    
    LayerColor * layerColor = LayerColor::create(Color4B(0, 0, 0, 200));
    addChild(layerColor);
//    layerColor->runAction(FadeTo::create(0.3, 200));
    
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
    Sprite * getIcon = Sprite::create(ImagePath("over_get_icon.png"));
    getIcon->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.42,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4);
    addChild(getIcon);
    
    Label * goldLabel = Label::createWithTTF(StringUtils::format("%d",_G_D->getGoldNum()),
                                             "fonts/Arial Black.ttf",
                                             30);
    goldLabel->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.52,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4);
    goldLabel->setAdditionalKerning(-3);
    goldLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    addChild(goldLabel);
    
    Sprite * jinbiIcon = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbiIcon->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.6,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4);
    addChild(jinbiIcon);
    
    int userGold = _G_U->getUserGold() + _G_D->getGoldNum();
    _G_U->setUserGold(userGold);
    
    Menu * buttonMenu = NULL;
//    if (m_overStatus == o_win)
//    {
        Sprite * title = Sprite::create(ImagePath("overScene_win.png"));
        title->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                           m_visibleOrigin.y + m_visibleSize.height * 0.58);
        addChild(title);
        MenuItemImage * gotoShopButton = MenuItemImage::create(ImagePath("overScene_toShop.png"),
                                                           ImagePath("overScene_toShop.png"),
                                                           CC_CALLBACK_1( GameOverScene::gotoShop, this));
        gotoMapButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 - widthOffset,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.22);
        restartButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.22);
        gotoShopButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 + widthOffset,
                                m_visibleOrigin.y + m_visibleSize.height * 0.22);
        
//        gotoMapButton->setScale(0.9);
//        restartButton->setScale(0.9);
//        gotoShopButton->setScale(0.9);
        buttonMenu = Menu::create(gotoMapButton,restartButton,gotoShopButton, NULL);
        
        GuanqiaModel * curGuanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
        GuanqiaModel * nextGuanqia = GuanQiaManager::getInstance()->getGuanqiaById(curGuanqia->getUnlockMission());
        nextGuanqia->unlockGuanqia();
        GunManager::getInstance()->checkUnlock();
        PropManager::getInstance()->checkUnlock();
        GunManager::getInstance()->saveBullet();
//    }else
//    {
//        Sprite * title = Sprite::create(ImagePath("overScene_title.png"));
//        title->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
//                           m_visibleOrigin.y + m_visibleSize.height * 0.58);
//        addChild(title);
//        gotoMapButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 - widthOffset * 0.7,
//                                   m_visibleOrigin.y + m_visibleSize.height * 0.22);
//        restartButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 + widthOffset * 0.7,
//                                   m_visibleOrigin.y + m_visibleSize.height * 0.22);
//        gotoMapButton->setScale(0.9);
//        restartButton->setScale(0.9);
//        buttonMenu = Menu::create(gotoMapButton,restartButton, NULL);
//    }
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,200);
    
    _G_D->resetGameData();
    
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
void GameOverScene::gotoShop(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameShopScene::scene());
}
//void GameOverScene::nextGuanqia(cocos2d::Ref *pSender)
//{
//    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
//    GuanqiaModel * curGuanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
//    GuanqiaModel * nextGuanqia = GuanQiaManager::getInstance()->getGuanqiaById(curGuanqia->getUnlockMission());
//    Director::getInstance()->replaceScene(GameLoadingScene::scene(nextGuanqia->getId()));
//}

bool GameOverScene::touchBegan(Touch *touch, Event *event)
{
    return true;
}