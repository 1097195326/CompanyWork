//
//  ShopGunItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#include "ShopGunItemScrollHeadler.h"
#include "GunManager.h"
//#include "PropManager.h"
//#include "DefenseBuildingManager.h"
#include "GameUser.h"
#include "GameShowLevelupLayer.h"
#include "GameSprite.h"
#include "GameShowDiscLayer.h"

ShopGunItemScrollHeadler::ShopGunItemScrollHeadler(int index)
{
    setIndex(index);
    
    initGunView();
    
}
ShopGunItemScrollHeadler::~ShopGunItemScrollHeadler()
{
    //    log("shop item scroll headler remove");
}
void ShopGunItemScrollHeadler::setGameShopScene(GameShopScene *shopScene)
{
    m_shopScene = shopScene;
}
void ShopGunItemScrollHeadler::initGunView()
{
    removeAllChildrenWithCleanup(true);
    
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    setSubject(gun);
    if (gun->isUnlock())
    {
        initUnlockGunView();
    }else
    {
        initLockGunView();
    }
    updateGunView();
}
void ShopGunItemScrollHeadler::initUnlockGunView()
{
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    
    Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
    addChild(itemBg);
    
    Size itemBgSize = itemBg->getContentSize();
    
    GameSprite * iconBg = new GameSprite(ImagePath("shopItemIconBg.png"));
    iconBg->autorelease();
    iconBg->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::showDiscView, this);
    
    //        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
    iconBg->setPosition(- itemBgSize.width * 0.35,
                        0);
    addChild(iconBg);
    
    Sprite * biaoSign = Sprite::create(ImagePath("shop_icon_sign.png"));
    biaoSign->setPosition(- itemBgSize.width * 0.41,
                          itemBgSize.height * 0.2);
    addChild(biaoSign);
    
    string gunModelId = gun->getModelId();
    string gunIconStr = StringUtils::format("%s_icon.png",gunModelId.c_str());
    string gunNameStr = StringUtils::format("%s_name.png",gunModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(gunIconStr));
    icon->setPosition(- itemBgSize.width * 0.35,
                      0);
    addChild(icon);
    
    Sprite * iconName = Sprite::create(ImagePath(gunNameStr));
    iconName->setPosition(-itemBgSize.width * 0.25
                          + iconName->getContentSize().width * 1,
                          itemBgSize.height * 0.2);
    addChild(iconName);
    
    m_upGradeButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
    m_upGradeButton->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::upGrade, this);
    m_upGradeButton->setPosition(itemBgSize.width * 0.29,
                                 -itemBgSize.height * 0.15);
    m_upGradeButton->autorelease();
    addChild(m_upGradeButton);

    m_buyButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
    m_buyButton->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::buy, this);
    m_buyButton->setPosition(-itemBgSize.width * 0.03,
                             -itemBgSize.height * 0.15);
    m_buyButton->autorelease();
    addChild(m_buyButton);
    
    m_bulletsLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 25);
    m_bulletsLabel->enableOutline(Color4B(0, 0, 0, 255),2);
    m_bulletsLabel->setPosition(- itemBgSize.width * 0.32,
                                -itemBgSize.height * 0.25);
    addChild(m_bulletsLabel,1);
    Sprite * bulletIcon = Sprite::create(ImagePath("shop_bullet_icon.png"));
    bulletIcon->setPosition(- itemBgSize.width * 0.27,
                            -itemBgSize.height * 0.25);
    addChild(bulletIcon,1);
    
    Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi1->setPosition(itemBgSize.width * 0.08,
                        -itemBgSize.height * 0.23);
    jinbi1->setScale(0.8);
    addChild(jinbi1,1);
    m_buyLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 30);
    m_buyLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_buyLabel->setPosition(-itemBgSize.width * 0.01,
                            -itemBgSize.height * 0.23);
    addChild(m_buyLabel,1);
    Sprite * buyLabel = Sprite::create(ImagePath("shopItemLabel2.png"));
    buyLabel->setPosition(-itemBgSize.width * 0.03,
                          -itemBgSize.height * 0.04);
    addChild(buyLabel,1);
    
    m_takeUpButton = MenuItemImage::create(ImagePath("shop_zhuanbei.png"),
                                           ImagePath("shop_zhuanbei.png"),
                                           CC_CALLBACK_1(ShopGunItemScrollHeadler::takeUp, this));
    
    m_takeUpButton->setPosition(itemBgSize.width * 0.5, 0);
    Menu * takeUpMenu = Menu::create(m_takeUpButton, NULL);
    takeUpMenu->setPosition(Point::ZERO);
    addChild(takeUpMenu);
    if (gun->isTakeUp())
    {
        m_takeUpButton->setVisible(false);
    }
    Sprite * upgradeLabel = Sprite::create(ImagePath("shopItemLabel1.png"));
    upgradeLabel->setPosition(itemBgSize.width * 0.29,
                              -itemBgSize.height * 0.04);
    addChild(upgradeLabel);
    
    m_progressBar = new ProgressBar("shopItemTiao1.png","shopItemTiao2.png");
    m_progressBar->setBarRight();
    m_progressBar->setPosition(itemBgSize.width * 0.32,
                               itemBgSize.height * 0.18);
    addChild(m_progressBar);
    
    m_levelUpLabel = Label::createWithTTF("LV", "fonts/Arial Black.ttf", 24);
    m_levelUpLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_levelUpLabel->setPosition(itemBgSize.width * 0.16,
                                itemBgSize.height * 0.18);
    addChild(m_levelUpLabel,1);
    
    m_upgradeLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 30);
    m_upgradeLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_upgradeLabel->setPosition(itemBgSize.width * 0.3,
                                -itemBgSize.height * 0.23);
    addChild(m_upgradeLabel,1);
    
    Sprite * jinbi2 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi2->setPosition(itemBgSize.width * 0.4,
                        -itemBgSize.height * 0.23);
    jinbi2->setScale(0.8);
    addChild(jinbi2);
}
void ShopGunItemScrollHeadler::initLockGunView()
{
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    
    Sprite * itemBg = Sprite::create(ImagePath("shopItemBg2.png"));
    addChild(itemBg);
    
    Size itemBgSize = itemBg->getContentSize();
    //
    string gunModelId = gun->getModelId();
    string gunIconStr = StringUtils::format("%s_grayicon.png",gunModelId.c_str());
    string gunNameStr = StringUtils::format("%s_name.png",gunModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(gunIconStr));
    icon->setPosition(- itemBgSize.width * 0.35,
                      0);
    addChild(icon);
    Sprite * lockIcon = Sprite::create(ImagePath("shopItemLockIcon.png"));
    lockIcon->setPosition(- itemBgSize.width * 0.3,
                          - itemBgSize.height * 0.18);
    addChild(lockIcon);
    
    Sprite * iconName = Sprite::create(ImagePath(gunNameStr));
    iconName->setPosition(-itemBgSize.width * 0.25
                          + iconName->getContentSize().width * 1,
                          itemBgSize.height * 0.2);
    addChild(iconName);
    
    m_unLockButton = new GameSprite(ImagePath("shopItemButonUnclock.png"));
    m_unLockButton->setPosition(itemBgSize.width * 0.29,
                                -itemBgSize.height * 0.15);
    m_unLockButton->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::unLock, this);
    m_unLockButton->autorelease();
    addChild(m_unLockButton);
    
    Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
    unlockName->setPosition(itemBgSize.width * 0.29,
                            -itemBgSize.height * 0.15);
    addChild(unlockName);
    
    Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",gun->getUnlockGold()),
                                               "fonts/Arial Black.ttf",
                                               20);
    unlockLabel->setPosition(itemBgSize.width * 0.29,
                             -itemBgSize.height * 0.28);
    addChild(unlockLabel);
}
void ShopGunItemScrollHeadler::updateGunView()
{
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    
    if (gun->isUnlock())
    {
        int bulletPrice = gun->getBulletPrice();
        float level = gun->getStrengthenLevel();
        float limitLevel = gun->getLimitLevel();
        int upgradeGold = gun->getStrengthenGold();
        int bullets = gun->getTotalBulletNum();
        
        if (gun->isMaxLevel())
        {
            m_upgradeLabel->setString("MAX");
        }else
        {
            m_upgradeLabel->setString(StringUtils::format("%d",upgradeGold));
        }
        
        m_levelUpLabel->setString(StringUtils::format("LV.%d",(int)level));
        m_progressBar->updatePercent(level/limitLevel * 100);
        m_buyLabel->setString(StringUtils::format("%d",bulletPrice));
        m_bulletsLabel->setString(StringUtils::format("%d",bullets));
        
        int userGold = GameUser::getInstance()->getUserGold();
        
        if (userGold >= bulletPrice)
        {
            m_buyButton->setEnabled(true);
        }else
        {
            m_buyButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
        if (gun->isDefaultGun() && bullets >= 12)
        {
            m_buyButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
        if (userGold >= upgradeGold && !gun->isMaxLevel())
        {
            m_upGradeButton->setEnabled(true);
        }else
        {
            m_upGradeButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
    }else
    {
        
    }
    
    
}
void ShopGunItemScrollHeadler::updateData()
{
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    if (gun->isUnlock())
    {
        if (gun->isTakeUp())
        {
            m_takeUpButton->setVisible(false);
        }else
        {
            m_takeUpButton->setVisible(true);
        }
    }
}
void ShopGunItemScrollHeadler::upGrade(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    bool sec = gun->addStrengthenLevel();
    if (sec)
    {
        m_shopScene->updateGoldView();
        updateGunView();
        GameShowLevelupLayer * showLayer = new GameShowLevelupLayer(gun->getModelId());
        showLayer->autorelease();
        m_shopScene->addChild(showLayer);
    }else
    {
        
    }
}
void ShopGunItemScrollHeadler::unLock(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    bool sec = gun->unlockGun();
    if (sec)
    {
        m_shopScene->updateGoldView();
        initGunView();
    }else
    {
        log("no enough money for unlock");
    }
}
void ShopGunItemScrollHeadler::buy(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    bool sec = gun->buyBullet();
    if (sec)
    {
        m_shopScene->updateGoldView();
        updateGunView();
    }else
    {
        
    }
}
void ShopGunItemScrollHeadler::takeUp(cocos2d::Ref *pSender)
{
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    GunManager::getInstance()->takeUpGun(gun->getId());
    
}
void ShopGunItemScrollHeadler::showDiscView(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Sprite * icon = (Sprite *) event->getCurrentTarget();
    Vec2 iconPoint = convertToWorldSpace(icon->getPosition());
    
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    std::string name = gun->getModelId();
    std::string disc = gun->getWeaponDescription();
    GameShowDiscLayer * showLayer = new GameShowDiscLayer(name,disc,iconPoint);
    showLayer->autorelease();
    m_shopScene->addChild(showLayer);
    
}