//
//  GameHomeScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/5.
//
//

#include "GameHomeScene.h"
#include "GameMapScene.h"
#include "GameShopScene.h"

#include "GameReliveLayer.h"


Scene * GameHomeScene::scene()
{
    Scene * scene = Scene::create();
    GameHomeScene * layer = GameHomeScene::create();
    scene->addChild(layer);
    
    return scene;
}
GameHomeScene::~GameHomeScene()
{
//    log("home scene release");
}
bool GameHomeScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Sprite * bg = Sprite::create(ImagePath("home_bg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg);
    
    MenuItem * toMapItem = MenuItemImage::create(ImagePath("home_toMap.png"), ImagePath("home_toMap.png"), CC_CALLBACK_1(GameHomeScene::toMapScene, this));
    MenuItem * toShopItem = MenuItemImage::create(ImagePath("home_toShop.png"), ImagePath("home_toShop.png"), CC_CALLBACK_1(GameHomeScene::toShopScene, this));
    MenuItem * toSetingItem = MenuItemImage::create(ImagePath("home_setting.png"), ImagePath("home_setting.png"), CC_CALLBACK_1(GameHomeScene::settingFunc, this));
    MenuItem * jiangbeiItem = MenuItemImage::create(ImagePath("home_jiangbei.png"), ImagePath("home_jiangbei.png"), CC_CALLBACK_1(GameHomeScene::jiangbeiFunc, this));
    
    toMapItem->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4 + 90);
    toShopItem->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4);
    toSetingItem->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                           m_visibleOrigin.y + m_visibleSize.height * 0.4 - 90);
    jiangbeiItem->setPosition(m_visibleOrigin.x + 100,
                              m_visibleOrigin.y + 100);
    Menu * buttonMenu = Menu::create(toMapItem,toShopItem,toSetingItem,jiangbeiItem, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu);
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic((MusicPath("shopMusic.mp3")).c_str(),true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    return true;
}

void GameHomeScene::toMapScene(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameMapScene::scene());
}
void GameHomeScene::toShopScene(cocos2d::Ref *pSender)
{
//    log("home scene to shop");
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameShopScene::scene());
}
void GameHomeScene::settingFunc(cocos2d::Ref *pSender)
{
//    GameReliveLayer * levelUp = new GameReliveLayer(NULL);
//    levelUp->autorelease();
//    addChild(levelUp);
}
void GameHomeScene::jiangbeiFunc(cocos2d::Ref *pSender)
{
    
}