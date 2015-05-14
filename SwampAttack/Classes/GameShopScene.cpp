//
//  GameShopScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameShopScene.h"

#include "ShopSelectMeumView.h"
#include "ShopItemScrollHeadler.h"
#include "GunManager.h"
#include "PropManager.h"
#include "DefenseBuildingManager.h"



bool GameShopScene::init()
{
    if (!LayerColor::init())
    {
        return false;
    }
    PropManager::getInstance();
    
    Sprite * bg = Sprite::create(ImagePath("shopBg.png"));
    bg->setPosition(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg);
    Sprite * bg2 = Sprite::create(ImagePath("shopBg2.png"));
    bg2->setPosition(visibleOrigin.x + visibleSize.width * 0.5, visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg2);
    Sprite * scrollBg = Sprite::create(ImagePath("shopScrollBg.png"));
    scrollBg->setPosition(bg2->getTextureRect().size.width * 0.5, bg2->getTextureRect().size.height * 0.368);
    bg2->addChild(scrollBg);
    //--- scroll view  for 4 --------
    m_scrollViews.reserve(4);
    for (int i = 0; i < 4 ; ++i)
    {
        int num = 0;
        switch (i) {
            case 0:
                num = GunManager::getInstance()->getGunNum();
                break;
            case 1:
                num = PropManager::getInstance()->getPropNum();
                break;
            case 2:
                num = DefenseBuildingManager::getInstance()->getBuildingNum();
                break;
            case 3:
                num = 3;
                break;
        }
        m_scrollViews[i] = new GameVerticalScrollHeadlerView(800,400,750,210,num);
        m_scrollViews[i]->setScrollControllerContentWidth(800);
        m_scrollViews[i]->setScrollControllerContentHeight(210 * num);
        m_scrollViews[i]->setGetHeadlerTarget(this);
        m_scrollViews[i]->setTag(i);
        m_scrollViews[i]->initView();
        m_scrollViews[i]->autorelease();
        m_scrollViews[i]->setPosition(bg2->getBoundingBox().origin.x, bg2->getBoundingBox().origin.y);
        bg2->addChild(m_scrollViews[i]);
        m_scrollViews[i]->setScale(0.0001);
    }
    //--- select menu view ----
    ShopSelectMenuView * menuView = new ShopSelectMenuView(4);
    menuView->autorelease();
    setSubject(menuView);
    menuView->setNormalSprite("shopItemNormal");
    menuView->setSelectSprite("shopItemSelect");
    menuView->setIconSprite("shopItemIcon");
    menuView->checkIndex();
    menuView->setPosition(bg2->getTextureRect().size.width * 0.5, bg2->getTextureRect().size.height * 0.8);
    bg2->addChild(menuView);
    
//    MenuItemImage * upButton = MenuItemImage::create(ImagePath("shopItemButtonNormal.png"),
//                                          ImagePath("shopItemButtonNormal.png"),
//                                          CC_CALLBACK_1(GameShopScene::upGrade, this));
//    
////    upButton->setNormalImage()
//    
//    Menu * buttonMenu = Menu::create(upButton, NULL);
//    addChild(buttonMenu);
//    Timer::
    struct timeval now;
    struct tm * time;
    gettimeofday(&now, NULL);
    
    time = localtime(&now.tv_sec);
    
    log("year :%d",time->tm_year + 1900);
    log("year :%ld",now.tv_sec * 1000);
    
    
    return true;
}
void GameShopScene::upGrade(cocos2d::Ref *pSender)
{
    log("--------");
}
void GameShopScene::updateData()
{
    ShopSelectMenuView * menuView = (ShopSelectMenuView *) m_sub;
    int itemIndex = menuView->getSelectIndex();
    
    for (int i = 0; i < 4 ; ++i)
    {
        if (itemIndex == i)
        {
            m_scrollViews[i]->setScale(1);
        }else
        {
             m_scrollViews[i]->setScale(0.0001);
        }
    }
}
GameScrollHeadler * GameShopScene::getHeadlerByIndex(int index,int viewTag)
{
    ShopItemScrollHeadler * headler = new ShopItemScrollHeadler(index, viewTag);
    headler->autorelease();
    return headler;
}