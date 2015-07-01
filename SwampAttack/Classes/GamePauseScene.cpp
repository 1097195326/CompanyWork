//
//  GamePauseScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/21.
//
//

#include "GamePauseScene.h"
#include "GameDirector.h"
#include "GuanQiaManager.h"
#include "EnemyManager.h"
#include "GunManager.h"

#include "GameMapScene.h"
#include "GameLoadingScene.h"


//Scene * GamePauseScene::scene(RenderTexture * rt)
//{
//    Scene * scene = Scene::create();
//    GamePauseScene * layer = GamePauseScene::create();
//    scene->addChild(layer,1);
//    
//    Sprite * bg = Sprite::createWithTexture(rt->getSprite()->getTexture());
//    bg->setPosition(m_visibleSize.width * 0.5,m_visibleSize.height * 0.5);
//    bg->setFlippedY(true);
//    bg->setColor(Color3B::GRAY);
//    scene->addChild(bg);
//
//    return scene;
//}
GamePauseScene::~GamePauseScene()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
GamePauseScene::GamePauseScene(RenderTexture * rt)
{
    init();
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(GamePauseScene::touchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    Sprite * scenebg = Sprite::createWithTexture(rt->getSprite()->getTexture());
    scenebg->setPosition(m_visibleSize.width * 0.5,m_visibleSize.height * 0.5);
    scenebg->setFlippedY(true);
    scenebg->setColor(Color3B::GRAY);
    addChild(scenebg);
    
    Sprite * bg = Sprite::create(ImagePath("pauseScene_bg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg);
    
    Sprite * pauseSpr = Sprite::create(ImagePath("pause_title.png"));
    Size bgSize = bg->getContentSize();
    pauseSpr->setPosition(bgSize.width * 0.5,bgSize.height * 0.5);
    bg->addChild(pauseSpr);
    
    int widthOffset = 100;
    
    MenuItemImage * gotoMapButton = MenuItemImage::create(ImagePath("overScene_tomap.png"),
                                                          ImagePath("overScene_tomap.png"),
                                                          CC_CALLBACK_1( GamePauseScene::gotoMap, this));
    gotoMapButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 - widthOffset,
                               m_visibleOrigin.y + m_visibleSize.height * 0.25);
    
    MenuItemImage * restartButton = MenuItemImage::create(ImagePath("overScene_restart.png"),
                                                          ImagePath("overScene_restart.png"),
                                                          CC_CALLBACK_1( GamePauseScene::restartGame, this));
    restartButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                               m_visibleOrigin.y + m_visibleSize.height * 0.25);
    
    MenuItemImage * continueButton = MenuItemImage::create(ImagePath("overScene_next.png"),
                                                           ImagePath("overScene_next.png"),
                                                           CC_CALLBACK_1( GamePauseScene::continueGame, this));
    continueButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5 + widthOffset,
                                m_visibleOrigin.y + m_visibleSize.height * 0.25);
    
    Menu * buttonMenu = Menu::create(gotoMapButton,restartButton,continueButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,200);
    
    GunManager::getInstance()->saveBullet();
}
void GamePauseScene::setFightLayer(GameFightScene *layer)
{
    m_fightLayer = layer;
}
void GamePauseScene::continueGame(cocos2d::Ref *pSender)
{
    m_fightLayer->resumeGameActions();
    removeFromParentAndCleanup(true);
    _G_D->continueGame();
}
void GamePauseScene::restartGame(cocos2d::Ref *pSender)
{
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    
    _G_D->resetGameData();
    
    GuanqiaModel * guanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
    Director::getInstance()->replaceScene(GameLoadingScene::scene(guanqia->getId()));
}
void GamePauseScene::gotoMap(cocos2d::Ref *pSender)
{
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    
    _G_D->resetGameData();
    Director::getInstance()->replaceScene(GameMapScene::scene());
}
bool GamePauseScene::touchBegan(Touch *touch, Event *event)
{
    log("------ ");
    return true;
}