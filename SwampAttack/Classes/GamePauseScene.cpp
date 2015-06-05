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
#include "GameFightScene.h"

#include "GameMapScene.h"


Scene * GamePauseScene::scene(RenderTexture * rt)
{
    Scene * scene = Scene::create();
    GamePauseScene * layer = GamePauseScene::create();
    scene->addChild(layer,1);
    
    Sprite * bg = Sprite::createWithTexture(rt->getSprite()->getTexture());
    bg->setPosition(m_visibleSize.width * 0.5,m_visibleSize.height * 0.5);
    bg->setFlippedY(true);
    bg->setColor(Color3B::GRAY);
    scene->addChild(bg);
    
    return scene;
}

bool GamePauseScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Sprite * bg = Sprite::create(ImagePath("pauseScene_bg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg);
    
    MenuItemImage * gotoMapButton = MenuItemImage::create(ImagePath("overScene_tomap.png"),
                                                          ImagePath("overScene_tomap.png"),
                                                          CC_CALLBACK_1( GamePauseScene::gotoMap, this));
    gotoMapButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.45,
                                m_visibleOrigin.y + m_visibleSize.height * 0.35);
    
    MenuItemImage * restartButton = MenuItemImage::create(ImagePath("pauseScene_restart.png"),
                                                        ImagePath("pauseScene_restart.png"),
                                                        CC_CALLBACK_1( GamePauseScene::restartGame, this));
    restartButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                             m_visibleOrigin.y + m_visibleSize.height * 0.35);
    
    MenuItemImage * continueButton = MenuItemImage::create(ImagePath("pauseScene_continue.png"),
                                                           ImagePath("pauseScene_continue.png"),
                                                           CC_CALLBACK_1( GamePauseScene::continueGame, this));
    continueButton->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.55,
                                m_visibleOrigin.y + m_visibleSize.height * 0.35);
    
    Menu * buttonMenu = Menu::create(gotoMapButton,restartButton,continueButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,200);
    
    
    return true;
}
void GamePauseScene::continueGame(cocos2d::Ref *pSender)
{
    Director::getInstance()->popScene();
    _G_D->continueGame();
}
void GamePauseScene::restartGame(cocos2d::Ref *pSender)
{
    GuanqiaModel * guanqia = GuanQiaManager::getInstance()->getCurrentGuanqia();
    EnemyManager::getInstance()->setData(guanqia->getMonsters());
    
    Director::getInstance()->replaceScene(GameFightScene::scene());
}
void GamePauseScene::gotoMap(cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(GameMapScene::scene());
}