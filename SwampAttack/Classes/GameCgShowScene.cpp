//
//  GameCgShowScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/8/10.
//
//

#include "GameCgShowScene.h"
#include "GameHomeScene.h"


Scene * GameCgShowScene::scene()
{
    Scene * scene = Scene::create();
    GameCgShowScene * layer = GameCgShowScene::create();
    scene->addChild(layer);
    
    return scene;
}
GameCgShowScene::~GameCgShowScene()
{
    //    log("home scene release");
    unschedule(CC_SCHEDULE_SELECTOR(GameCgShowScene::updateCg));
}
bool GameCgShowScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    m_index = 2;
    
    m_spr1 = Sprite::create(ImagePath("CG01.jpg"));
    m_spr1->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5 - 40);
    addChild(m_spr1);
    m_spr1->setScale(1.35);
    
//    MenuItem * toMapItem = MenuItemImage::create(ImagePath("home_toMap.png"), ImagePath("home_toMap.png"), CC_CALLBACK_1(GameCgShowScene::skipToHomeScene, this));
//    
//    toMapItem->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
//                           m_visibleOrigin.y + m_visibleSize.height * 0.4 + 90);
//    Menu * buttonMenu = Menu::create(toMapItem, NULL);
//    buttonMenu->setPosition(Point::ZERO);
//    addChild(buttonMenu);
    
    schedule(CC_SCHEDULE_SELECTOR(GameCgShowScene::updateCg), 2.5, 4, 2.5);
    
    return true;
}
void GameCgShowScene::updateCg(float data)
{
//    m_spr2 = Sprite::create(ImagePath(StringUtils::format("CG%002d.jpg",m_index)));
//    m_spr2->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
//                        m_visibleOrigin.y + m_visibleSize.height * 0.5);
//    addChild(m_spr2);

    if (m_index == 5)
    {
        skipToHomeScene(NULL);
    }else
    {
        m_spr1->setTexture(ImagePath(StringUtils::format("CG%002d.jpg",m_index)));
        ++m_index;
    }
    
}
void GameCgShowScene::swapEnd()
{
    
}
void GameCgShowScene::skipToHomeScene(cocos2d::Ref *pSender)
{
//    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameHomeScene::scene());
}