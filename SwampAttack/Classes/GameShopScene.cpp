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
#include "GameUser.h"



bool GameShopScene::init()
{
    if (!LayerColor::init())
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
    m_goldLabel = Label::createWithTTF(StringUtils::format("%d",_G_U->getUserGold()),
                                       "fonts/American Typewriter.ttf",
                                       35);
    m_goldLabel->setPosition(visibleOrigin.x + visibleSize.width * 0.55,
                             visibleOrigin.y + visibleSize.height * 0.94);
    addChild(m_goldLabel);
    
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
    headler->setGameShopScene(this);
    headler->autorelease();
    return headler;
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
    log("--------2");
}