//
//  GameOverScene.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/6/1.
//
//

#include "GameOverScene.h"
#include "GameFightScene.h"
#include "GameMapScene.h"


#include "GameDirector.h"
#include "EnemyManager.h"
#include "GuanQiaManager.h"
#include "GameLoading.h"


Scene * GameOverScene::scene(GameOverStatus status)
{
    Scene * scene = Scene::create();
    GameOverScene * layer = new GameOverScene(status);
    layer->autorelease();
    layer->init();
    scene->addChild(layer,1);
    
    return scene;
}
GameOverScene::GameOverScene(GameOverStatus status)
{
    m_overStatus = status;
}
bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    
    Sprite * bg = Sprite::create(ImagePath("overScene_bg.png"));
    bg->setPosition(visibleOrigin.x + visibleSize.width * 0.5,
                    visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg);
    
    
    
    int widthOffset = 60;
    MenuItemImage * gotoMapButton = MenuItemImage::create(ImagePath("overScene_tomap.png"),
                                                       ImagePath("overScene_tomap.png"),
                                                       CC_CALLBACK_1( GameOverScene::gotoMap, this));
    MenuItemImage * restartButton = MenuItemImage::create(ImagePath("overScene_restart.png"),
                                                          ImagePath("overScene_restart.png"),
                                                          CC_CALLBACK_1( GameOverScene::restartGame, this));
    Menu * buttonMenu = NULL;
    if (m_overStatus == o_win)
    {
        MenuItemImage * nextButton = MenuItemImage::create(ImagePath("overScene_next.png"),
                                                           ImagePath("overScene_next.png"),
                                                           CC_CALLBACK_1( GameOverScene::nextGuanqia, this));
        gotoMapButton->setPosition(visibleOrigin.x + visibleSize.width * 0.5 - widthOffset,
                                   visibleOrigin.y + visibleSize.height * 0.35);
        restartButton->setPosition(visibleOrigin.x + visibleSize.width * 0.5,
                                   visibleOrigin.y + visibleSize.height * 0.35);
        nextButton->setPosition(visibleOrigin.x + visibleSize.width * 0.5 + widthOffset,
                                visibleOrigin.y + visibleSize.height * 0.35);
        buttonMenu = Menu::create(gotoMapButton,restartButton,nextButton, NULL);
        
        GuanqiaModel * curGuanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
        GuanqiaModel * nextGuanqia = GuanQiaManager::getInstance()->getGuanqiaById(curGuanqia->getUnlockMission());
        nextGuanqia->unlockGuanqia();
    }else
    {
        gotoMapButton->setPosition(visibleOrigin.x + visibleSize.width * 0.5 - widthOffset * 0.7,
                                   visibleOrigin.y + visibleSize.height * 0.35);
        restartButton->setPosition(visibleOrigin.x + visibleSize.width * 0.5 + widthOffset * 0.7,
                                   visibleOrigin.y + visibleSize.height * 0.35);
        buttonMenu = Menu::create(gotoMapButton,restartButton, NULL);
    }
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,200);
    
    
    return true;
}
void GameOverScene::restartGame(cocos2d::Ref *pSender)
{
    GameLoading::loadFrames();
    GuanqiaModel * guanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
    EnemyManager::getInstance()->setData(guanqia->getMonsters());
    
    
    Director::getInstance()->replaceScene(GameFightScene::scene());
}
void GameOverScene::gotoMap(cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(GameMapScene::scene());
}
void GameOverScene::nextGuanqia(cocos2d::Ref *pSender)
{
    GameLoading::loadFrames();
    GuanqiaModel * curGuanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
    GuanqiaModel * nextGuanqia = GuanQiaManager::getInstance()->getGuanqiaById(curGuanqia->getUnlockMission());
    GuanQiaManager::getInstance()->setCurrentGuanqiaId(nextGuanqia->getId());
    EnemyManager::getInstance()->setData(nextGuanqia->getMonsters());
    
    
    Director::getInstance()->replaceScene(GameFightScene::scene());
}