//
//  GameShopScene.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#include "GameShopScene.h"
#include "GameHomeScene.h"

#include "ShopSelectMenuView.h"
#include "GunManager.h"
#include "PropManager.h"
#include "DefenseBuildingManager.h"
#include "SpecialManager.h"

#include "GameUser.h"
#include "GameMapScene.h"
#include "ShopGunIcon.h"

#include "ShopGunItemScrollHeadler.h"
#include "ShopPropItemScrollHeadler.h"
#include "ShopBuildingItemScrollHeadler.h"
#include "ShopAwardItemScrollHeadler.h"

//Scene * GameShopScene::scene()
//{
//    Scene * scene = Scene::create();
//    GameShopScene * layer = GameShopScene::create();
//    scene->addChild(layer);
//    
//    return scene;
//}
GameShopScene::~GameShopScene()
{
//    log("shop scene release");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();

    m_scrollViews.clear();
}
bool GameShopScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    initShopView();
    initScrollView();

    string gunId = GunManager::getInstance()->getWillTakeUpGun();
    if (gunId.size() > 0)
    {
        GunManager::getInstance()->takeUpWillGun();
    }
    string propId = PropManager::getInstance()->getWillTakeUpProp();
    if (propId.size() > 0) {
        PropManager::getInstance()->takeUpWillProp();
    }
//    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
//    if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic((MusicPath("shopMusic.mp3")).c_str(),true);
    
    return true;
}

void GameShopScene::initShopView()
{
    Sprite * bg = Sprite::create(ImagePath("shopBg.png"));
    bg->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                    m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(bg);
    
    setItemBgSprite();
    
    MenuItemImage * homeButton = MenuItemImage::create(ImagePath("shopHomeButton.png"),
                                                       ImagePath("shopHomeButton.png"),
                                                       CC_CALLBACK_1(GameShopScene::homeButtonFunc, this));
    homeButton->setPosition(m_visibleOrigin.x + 60,
                            m_visibleOrigin.y + m_visibleSize.height - 60);
    MenuItemImage * backButton = MenuItemImage::create(ImagePath("shopBackButton.png"),
                                                       ImagePath("shopBackButton.png"),
                                                       CC_CALLBACK_1(GameShopScene::backButtonFunc, this));
    backButton->setPosition(m_visibleOrigin.x + m_visibleSize.width - 60,
                            m_visibleOrigin.y + m_visibleSize.height - 60);
    Menu * buttonMenu = Menu::create(homeButton,
                                     backButton,
                                     NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu,1);
}
void GameShopScene::initScrollView()
{
    Sprite * bg2 = Sprite::create(ImagePath("shopBg2.png"));
    bg2->setPosition(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                     m_visibleOrigin.y + m_visibleSize.height * 0.46);
    addChild(bg2);
    m_bg2 = bg2;
    Sprite * scrollBg = Sprite::create(ImagePath("shopScrollBg.png"));
    scrollBg->setPosition(bg2->getTextureRect().size.width * 0.5,
                          bg2->getTextureRect().size.height * 0.36 - 15);
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
                num = SpecialManager::getInstance()->getSpecialNum();
                break;
        }
        m_scrollViews[i] = new GameVerticalScrollHeadlerView(820,400,750,210,num);
        m_scrollViews[i]->setScrollControllerContentWidth(820);
        m_scrollViews[i]->setScrollControllerContentHeight(210 * num);
        m_scrollViews[i]->setGetHeadlerTarget(this);
        m_scrollViews[i]->setTag(i);
        m_scrollViews[i]->initView();
        m_scrollViews[i]->autorelease();
        m_scrollViews[i]->setPosition(bg2->getBoundingBox().origin.x - 20, bg2->getBoundingBox().origin.y);
        bg2->addChild(m_scrollViews[i],2);
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
//    menuView->setIconSprite("shopItemIcon");
    menuView->checkIndex();
    menuView->setPosition(bg2->getTextureRect().size.width * 0.5 -5,
                          bg2->getTextureRect().size.height * 0.8);
    bg2->addChild(menuView,5);
}
void GameShopScene::updateData()
{
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
    Vec2 v_p;
//    v_p = Vec2(750 * 0.5, 0.0 - 210 * (index + 1) + 400 + 210 * 0.5);
    v_p = Vec2(m_visibleSize.width * 0.5 - m_bg2->getPositionX() * 0.4 + 40,
               0.0 - 210 * (index + 1) + 400 + 210 * 0.5);
    
    GameScrollHeadler * r_headler = NULL;
    
    switch (viewTag) {
        case 0:
        {
            ShopGunItemScrollHeadler * headler = new ShopGunItemScrollHeadler(index);
            headler->setGameShopScene(this);
            r_headler = headler;
        }
            break;
        case 1:
        {
            ShopPropItemScrollHeadler * headler = new ShopPropItemScrollHeadler(index);
            headler->setGameShopScene(this);
            r_headler = headler;
        }
            break;
        case 2:
        {
            ShopBuildingItemScrollHeadler * headler = new ShopBuildingItemScrollHeadler(index);
            headler->setGameShopScene(this);
            r_headler = headler;
        }
            break;
        case 3:
        {
            ShopAwardItemScrollHeadler * headler = new ShopAwardItemScrollHeadler(index);
            headler->setGameShopScene(this);
            r_headler = headler;
        }
            break;
    }
    r_headler->autorelease();
    r_headler->setPosition(v_p);
    return r_headler;
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
void GameShopScene::setItemBgSprite()
{
    m_gunItembgSprite = Sprite::create();
    m_gunItembgSprite->setPosition(m_visibleOrigin.x + m_visibleSize.width - 65,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.4);
    addChild(m_gunItembgSprite,1);
    
    GunManager::getInstance()->setShopView(m_gunItembgSprite);
    
    m_gunItembgSprite->setVisible(false);
    //---
    m_propItembgSprite = Sprite::create();
    m_propItembgSprite->setPosition(m_visibleOrigin.x + m_visibleSize.width - 65,
                                   m_visibleOrigin.y + m_visibleSize.height * 0.5);
    addChild(m_propItembgSprite,1);
    
    PropManager::getInstance()->setShopView(m_propItembgSprite);
    
    m_propItembgSprite->setVisible(false);
}
void GameShopScene::homeButtonFunc(cocos2d::Ref *pSender)
{
//    log("shop scene to home");
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameHomeScene::scene());
}
void GameShopScene::backButtonFunc(cocos2d::Ref *pSender)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Director::getInstance()->replaceScene(GameMapScene::scene());
}