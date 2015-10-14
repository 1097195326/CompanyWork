//
//  MapGuanqiaButton.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/5/30.
//
//

#include "MapGuanqiaButton.h"
#include "GuanQiaManager.h"
#include "GameLoadingScene.h"
#include "BaseUtil.h"
#include "GameUser.h"
#include "AlertTextTool.h"
//#include "GameFightScene.h"
//#include "EnemyManager.h"
//#include "GameLoading.h"
//#include "GameDirector.h"

#include "MobClickCpp.h"

MapGuanqiaButton::MapGuanqiaButton(int sceneIndex, int index):
m_sceneIndex(sceneIndex),
m_index(index)
{
    init();
    //400001_1
    m_guanqiaId = StringUtils::format("40000%d_%d",(m_sceneIndex),m_index);
//    log("guan qia id:%s",guanqiaId.c_str());
    
    GuanqiaModel * guanQia = GuanQiaManager::getInstance()->getGuanqiaById(m_guanqiaId);
    setSubject(guanQia);
    
//    m_menuItem = MenuItemImage::create(ImagePath("map_button.png"),
//                                       ImagePath("map_button.png"),
//                                       CC_CALLBACK_1(MapGuanqiaButton::pressGuanqiaButtonFunc, this));
    
    int s_Indx = _G_U->getLastSceneIndex();
    int g_Indx = _G_U->getLastGuanqiaIndex();
    
//    log("s_i:%d",s_Indx);
//    log("g_i:%d",g_Indx);
    
    if (s_Indx == m_sceneIndex && g_Indx == m_index)
    {
        auto spriteFrameCache = SpriteFrameCache::getInstance();
        spriteFrameCache->addSpriteFramesWithFile(ImagePath("texiao2.plist"));
        Action * buttonAction = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("button_flash",6));
        Sprite * boSpr = Sprite::create();
        boSpr->setPosition(guanQia->getGuanqiaPoint());
        addChild(boSpr);
        boSpr->runAction(buttonAction);
    }
    
    m_menuItem = new GameSprite(ImagePath("map_button.png"));
    m_menuItem->m_touchMeCall =CC_CALLBACK_2(MapGuanqiaButton::pressGuanqiaButtonFunc, this);
    m_menuItem->autorelease();
    m_menuItem->setPosition(guanQia->getGuanqiaPoint());
    addChild(m_menuItem);
//    Menu * buttonMenu = Menu::create(m_menuItem, NULL);
//    buttonMenu->setPosition(Point::ZERO);
//    addChild(buttonMenu);
    
    Sprite * label = Sprite::create(ImagePath(StringUtils::format("map_label%d.png",m_index)));
    label->setPosition(guanQia->getGuanqiaPoint() + Vec2(0, 6));
    addChild(label);
    
    m_lockSprite = Sprite::create(ImagePath("map_buttonLock.png"));
    m_lockSprite->setPosition(guanQia->getGuanqiaPoint() + Vec2(0, 6));
    addChild(m_lockSprite);
    
    if (guanQia->isUnlock())
    {
        m_lockSprite->setVisible(false);
    }
    
}
MapGuanqiaButton::~MapGuanqiaButton()
{
    
}

void MapGuanqiaButton::updateData()
{
    
}
void MapGuanqiaButton::pressGuanqiaButtonFunc(Touch * touch, Event * event)
{
    log("enter guan qia  id : %s",m_guanqiaId.c_str());
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    
    GuanqiaModel * guanQia = GuanQiaManager::getInstance()->getGuanqiaById(m_guanqiaId);
    if (_G_U->getUserHealth() < 1)
    {
        AlertText(healthNoEnough, 40);
        return;
    }
    if (guanQia->isUnlock())
    {
        umeng::MobClickCpp::startLevel(m_guanqiaId.c_str());
        
        string musicName = StringUtils::format("sceneMusic%d.mp3",m_sceneIndex);
        SimpleAudioEngine::getInstance()->playBackgroundMusic((MusicPath(musicName)).c_str(),true);
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
        
        GuanQiaManager::getInstance()->setCurrentSceneIndex(m_sceneIndex);
        GuanQiaManager::getInstance()->setCurrentGuanqiaIndex(m_sceneIndex,m_index);
        
        Director::getInstance()->replaceScene(GameLoadingScene::scene(m_guanqiaId));
    }else
    {
//        log("this guan qia is lcok");
        AlertText(guanqiaIslock, 40);
    }
}
