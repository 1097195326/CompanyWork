//
//  GameShopScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameShopScene.h"

#include "ShopSelectMenuView.h"
#include "GunManager.h"
#include "PropManager.h"
#include "DefenseBuildingManager.h"
#include "GameUser.h"
#include "GameMapScene.h"
#include "ShopGunIcon.h"

#include "ShopGunItemScrollHeadler.h"
#include "ShopPropItemScrollHeadler.h"
#include "ShopBuildingItemScrollHeadler.h"
#include "ShopAwardItemScrollHeadler.h"



bool GameShopScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    PropManager::getInstance();
    
    Sprite * bg = Sprite::create(ImagePath("shopBg.png"));
    bg->setPosition(visibleOrigin.x + visibleSize.width * 0.5,
                    visibleOrigin.y + visibleSize.height * 0.5);
    addChild(bg);
    Sprite * upBg = Sprite::create(ImagePath("shopUpBg.png"));
    upBg->setPosition(visibleOrigin.x + visibleSize.width * 0.5,
                      visibleOrigin.y + visibleSize.height - upBg->getContentSize().height * 0.5);
    addChild(upBg);
    
    Sprite * bg2 = Sprite::create(ImagePath("shopBg2.png"));
    bg2->setPosition(visibleOrigin.x + visibleSize.width * 0.5,
                     visibleOrigin.y + visibleSize.height * 0.46);
    addChild(bg2);
    Sprite * scrollBg = Sprite::create(ImagePath("shopScrollBg.png"));
    scrollBg->setPosition(bg2->getTextureRect().size.width * 0.5,
                          bg2->getTextureRect().size.height * 0.368);
    bg2->addChild(scrollBg);
    
    m_goldLabel = Label::createWithTTF(StringUtils::format("%d",_G_U->getUserGold()),
                                       "fonts/American Typewriter.ttf",
                                       35);
    m_goldLabel->setPosition(visibleOrigin.x + visibleSize.width * 0.55,
                             visibleOrigin.y + visibleSize.height * 0.94);
    addChild(m_goldLabel);
    
    setItemBgSprite();
    
    m_healthSprites.reserve(5);
    for (int i = 0; i < 5; ++i) {
        Sprite * xinBg = Sprite::create(ImagePath("shopXinBg.png"));
        Sprite * xin = Sprite::create(ImagePath("shopXinIcon.png"));
        
        Vec2 xinP = Vec2(visibleOrigin.x + visibleSize.width * 0.16 + xinBg->getContentSize().width * i,
                         visibleOrigin.y + visibleSize.height * 0.94);
        xinBg->setPosition(xinP);
        xin->setPosition(xinP);
        addChild(xinBg);
        addChild(xin);
        xin->setVisible(false);
        m_healthSprites.push_back(xin);
    }
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
//    m_scrollView = new GameVerticalScrollHeadlerView(800,400,750,210,0);
//    m_scrollView->setScrollControllerContentWidth(800);
//    m_scrollView->setGetHeadlerTarget(this);
//    m_scrollView->autorelease();
//    m_scrollView->setPosition(bg2->getBoundingBox().origin.x, bg2->getBoundingBox().origin.y);
//    bg2->addChild(m_scrollView);
    
    //--- select menu view ----
    ShopSelectMenuView * menuView = new ShopSelectMenuView(4);
    menuView->autorelease();
    setSubject(menuView);
    menuView->setNormalSprite("shopItemNormal");
    menuView->setSelectSprite("shopItemSelect");
    menuView->setIconSprite("shopItemIcon");
    menuView->checkIndex();
    menuView->setPosition(bg2->getTextureRect().size.width * 0.5,
                          bg2->getTextureRect().size.height * 0.8);
    bg2->addChild(menuView);
    
    MenuItemImage * homeButton = MenuItemImage::create(ImagePath("shopHomeButton.png"),
                                                       ImagePath("shopHomeButton.png"),
                                                       CC_CALLBACK_1(GameShopScene::homeButtonFunc, this));
    homeButton->setPosition(visibleOrigin.x + homeButton->getContentSize().width * 0.5,
                            visibleOrigin.y + visibleSize.height - homeButton->getContentSize().height * 0.5);
    MenuItemImage * backButton = MenuItemImage::create(ImagePath("shopBackButton.png"),
                                                       ImagePath("shopBackButton.png"),
                                                       CC_CALLBACK_1(GameShopScene::backButtonFunc, this));
    backButton->setPosition(visibleOrigin.x + visibleSize.width - backButton->getContentSize().width * 0.5 ,
                            visibleOrigin.y + visibleSize.height - backButton->getContentSize().height * 0.5);
    Menu * buttonMenu = Menu::create(homeButton,backButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu);
    //
    
    
    _G_U->attach(this);
    return true;
}
GameShopScene::~GameShopScene()
{
    _G_U->detach(this);
}

void GameShopScene::updateData()
{
    int userHealth = _G_U->getUserHealth();
    for (int i = 0; i < 5; ++i)
    {
        if (i < userHealth)
        {
            m_healthSprites[i]->setVisible(true);
        }else
        {
            m_healthSprites[i]->setVisible(false);
        }
    }
    ShopSelectMenuView * menuView = (ShopSelectMenuView *) m_sub;
    int itemIndex = menuView->getSelectIndex();
    
    visibelItemBg(itemIndex);
    
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
//    int num = 0;
//    switch (itemIndex) {
//        case 0:
//            num = GunManager::getInstance()->getGunNum();
//            break;
//        case 1:
//            num = PropManager::getInstance()->getPropNum();
//            break;
//        case 2:
//            num = DefenseBuildingManager::getInstance()->getBuildingNum();
//            break;
//        case 3:
//            num = 3;
//            break;
//    }
//    m_scrollView->setTag(itemIndex);
//    m_scrollView->setScrollControllerContentHeight(210 * num);
//    m_scrollView->reSetTotalCount(num);
//    m_scrollView->reSetView();
}
GameScrollHeadler * GameShopScene::getHeadlerByIndex(int index,int viewTag)
{
    switch (viewTag) {
        case 0:
        {
            ShopGunItemScrollHeadler * headler = new ShopGunItemScrollHeadler(index);
            headler->setGameShopScene(this);
            headler->autorelease();
            return headler;
        }
            break;
        case 1:
        {
            ShopPropItemScrollHeadler * headler = new ShopPropItemScrollHeadler(index);
            headler->setGameShopScene(this);
            headler->autorelease();
            return headler;
        }
            break;
        case 2:
        {
            ShopBuildingItemScrollHeadler * headler = new ShopBuildingItemScrollHeadler(index);
            headler->setGameShopScene(this);
            headler->autorelease();
            return headler;
        }
            break;
        case 3:
        {
            ShopAwardItemScrollHeadler * headler = new ShopAwardItemScrollHeadler(index);
            headler->setGameShopScene(this);
            headler->autorelease();
            return headler;
        }
            break;
    }
    return NULL;
}
void GameShopScene::visibelItemBg(int index)
{
    switch (index) {
        case 0:
            m_gunItembgSprite->setVisible(true);
            m_propItembgSprite->setVisible(false);
            break;
        case 1:
            m_gunItembgSprite->setVisible(false);
            m_propItembgSprite->setVisible(true);
            break;
        default:
            m_gunItembgSprite->setVisible(false);
            m_propItembgSprite->setVisible(false);
            break;
    }
}
void GameShopScene::updateGoldView()
{
    m_goldLabel->setString(StringUtils::format("%d",_G_U->getUserGold()));
}
void GameShopScene::homeButtonFunc(cocos2d::Ref *pSender)
{
    log("--------1");
}
void GameShopScene::backButtonFunc(cocos2d::Ref *pSender)
{
    Director::getInstance()->replaceScene(GameMapScene::scene());
}
void GameShopScene::setItemBgSprite()
{
    m_gunItembgSprite = Sprite::create();
    m_gunItembgSprite->setPosition(visibleOrigin.x + visibleSize.width - 60,
                                   visibleOrigin.y + visibleSize.height * 0.4);
    addChild(m_gunItembgSprite);
    
    GunManager::getInstance()->setShopView(m_gunItembgSprite);
    
    m_gunItembgSprite->setVisible(false);
    //---
    m_propItembgSprite = Sprite::create();
    m_propItembgSprite->setPosition(visibleOrigin.x + visibleSize.width - 60,
                                   visibleOrigin.y + visibleSize.height * 0.5);
    addChild(m_propItembgSprite);
    
    PropManager::getInstance()->setShopView(m_propItembgSprite);
    
    m_propItembgSprite->setVisible(false);
}