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
#include "GameMapManager.h"
#include "GameReliveLayer.h"
#include "BaseUtil.h"

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
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("welcomeFlash.plist"));
    
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
    Menu * buttonMenu = Menu::create(toMapItem,toShopItem,jiangbeiItem, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu);
    
    ActionInterval * jiangbeiFlash = RepeatForever::create(Sequence::create(FadeIn::create(0.1),
                                                                            BaseUtil::makeAnimateWithNameAndIndex("welcome_flash_a", 9),
                                                                            FadeOut::create(0.1),
                                                                            DelayTime::create(2.5),
                                                                            NULL));
    ActionInterval * dengLeftFlash = RepeatForever::create(Sequence::create(DelayTime::create(3),
                                                                            FadeIn::create(0.1),
                                                                            BaseUtil::makeAnimateWithNameAndIndex("welcome_flash_b", 4),
                                                                            FadeOut::create(0.1),
                                                                            NULL));
    ActionInterval * dengRightFlash = RepeatForever::create(Sequence::create(FadeIn::create(0.1),
                                                                             BaseUtil::makeAnimateWithNameAndIndex("welcome_flash_c", 4),
                                                                             FadeOut::create(0.1),
                                                                             DelayTime::create(4),
                                                                             NULL));
    ActionInterval * zuiSmokeFlash = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("welcome_smoke_a", 16));
    ActionInterval * qiangSmokeFlash = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("welcome_smoke_b", 27));
    ActionInterval * danSmokeFlash = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("welcome_smoke_c", 27));
    ActionInterval * qiangXingFlash = RepeatForever::create(Sequence::create(DelayTime::create(1),
                                                                             FadeIn::create(0.1),
                                                                             BaseUtil::makeAnimateWithNameAndIndex("welcome_star", 24),
                                                                             FadeOut::create(0.1),
                                                                             NULL));
    
    Sprite * jiangbeiFlash_S = Sprite::create();
    jiangbeiFlash_S->setPosition(_G_M_M->welcomeJiangbeiPoint_flash);
    addChild(jiangbeiFlash_S);
    jiangbeiFlash_S->runAction(jiangbeiFlash);
    
    Sprite * dengLeftFlash_S = Sprite::create();
    dengLeftFlash_S->setPosition(_G_M_M->welcomeDengleftPoint_flash);
    addChild(dengLeftFlash_S);
    dengLeftFlash_S->runAction(dengLeftFlash);
    
    Sprite * dengRightFlash_S = Sprite::create();
    dengRightFlash_S->setPosition(_G_M_M->welcomeDengrightPoint_flash);
    addChild(dengRightFlash_S);
    dengRightFlash_S->runAction(dengRightFlash);
    
    Sprite * zuiSmokeFlash_S = Sprite::create();
    zuiSmokeFlash_S->setPosition(_G_M_M->welcomeZuiSmokePoint_flash);
    addChild(zuiSmokeFlash_S);
    zuiSmokeFlash_S->runAction(zuiSmokeFlash);
    
    Sprite * qiangSmokeFlash_S = Sprite::create();
    qiangSmokeFlash_S->setPosition(_G_M_M->welcomeQiangSmokepoint_flash);
    addChild(qiangSmokeFlash_S);
    qiangSmokeFlash_S->runAction(qiangSmokeFlash);
    
    Sprite * danSmokeFlash_S = Sprite::create();
    danSmokeFlash_S->setPosition(_G_M_M->welcomeDanyanSmokePoint_flash);
    addChild(danSmokeFlash_S);
    danSmokeFlash_S->runAction(danSmokeFlash);
    
    Sprite * qiangXingFlash_S = Sprite::create();
    qiangXingFlash_S->setPosition(_G_M_M->welcomeQiangXingSmokePoint_flash);
    addChild(qiangXingFlash_S);
    qiangXingFlash_S->runAction(qiangXingFlash);
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic((MusicPath("shopMusic.mp3")).c_str(),true);
//    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
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