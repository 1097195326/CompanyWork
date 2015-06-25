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
    GameSprite * iconBg = new GameSprite(ImagePath("shopItemIconBg.png"));
    iconBg->autorelease();
    iconBg->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::showDiscView, this);
    
    //        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
    iconBg->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
    addChild(iconBg);
    
    string gunModelId = gun->getModelId();
    string gunIconStr = StringUtils::format("%s_icon.png",gunModelId.c_str());
    string gunNameStr = StringUtils::format("%s_name.png",gunModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(gunIconStr));
    icon->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
    addChild(icon);
    
    Sprite * iconName = Sprite::create(ImagePath(gunNameStr));
    iconName->setPosition(-itemBg->getContentSize().width * 0.25 + iconName->getContentSize().width * 1, itemBg->getContentSize().height * 0.18);
    addChild(iconName);
    
    m_upGradeButton = MenuItemImage::create(ImagePath("shopItemButtonNormal.png"),
                                            ImagePath("shopItemButtonNormal.png"),
                                            CC_CALLBACK_1(ShopGunItemScrollHeadler::upGrade, this));
    
    m_upGradeButton->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
    m_buyButton = MenuItemImage::create(ImagePath("shopItemButtonNormal.png"),
                                        ImagePath("shopItemButtonNormal.png"),
                                        CC_CALLBACK_1(ShopGunItemScrollHeadler::buy, this));
    
    m_buyButton->setPosition(-itemBg->getContentSize().width * 0.03, -itemBg->getContentSize().height * 0.15);
    Menu * buttonMenu = Menu::create(m_buyButton,m_upGradeButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu);
    
    m_bulletsLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 20);
    m_bulletsLabel->setColor(Color3B(0, 0, 0));
    m_bulletsLabel->setPosition(- itemBg->getContentSize().width * 0.3, -itemBg->getContentSize().height * 0.25);
    addChild(m_bulletsLabel,1);
    Sprite * bulletIcon = Sprite::create(ImagePath("shop_bullet_icon.png"));
    bulletIcon->setPosition(- itemBg->getContentSize().width * 0.26, -itemBg->getContentSize().height * 0.25);
    addChild(bulletIcon,1);
    
    Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi1->setPosition(itemBg->getContentSize().width * 0.08, -itemBg->getContentSize().height * 0.23);
    jinbi1->setScale(0.8);
    addChild(jinbi1,1);
    m_buyLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 20);
    m_buyLabel->setPosition(itemBg->getContentSize().width * 0.02, -itemBg->getContentSize().height * 0.23);
    addChild(m_buyLabel,1);
    Sprite * buyLabel = Sprite::create(ImagePath("shopItemLabel2.png"));
    buyLabel->setPosition(-itemBg->getContentSize().width * 0.03, -itemBg->getContentSize().height * 0.1);
    addChild(buyLabel,1);
    
    
    
    m_takeUpButton = MenuItemImage::create(ImagePath("shop_zhuanbei.png"),
                                           ImagePath("shop_zhuanbei.png"),
                                           CC_CALLBACK_1(ShopGunItemScrollHeadler::takeUp, this));
    
    m_takeUpButton->setPosition(itemBg->getContentSize().width * 0.5, 0);
    Menu * takeUpMenu = Menu::create(m_takeUpButton, NULL);
    takeUpMenu->setPosition(Point::ZERO);
    addChild(takeUpMenu);
    if (gun->isTakeUp())
    {
        m_takeUpButton->setVisible(false);
    }
    Sprite * upgradeLabel = Sprite::create(ImagePath("shopItemLabel1.png"));
    upgradeLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.1);
    addChild(upgradeLabel);
    
    Sprite * levelBg = Sprite::create(ImagePath("shopItemLevelBg.png"));
    levelBg->setPosition(itemBg->getContentSize().width * 0.13, itemBg->getContentSize().height * 0.18);
    addChild(levelBg);
    m_levelUpLabel = Label::createWithTTF("LV", "fonts/Arial Black.ttf", 20);
    m_levelUpLabel->setPosition(levelBg->getContentSize().width * 0.5, levelBg->getContentSize().height * 0.5);
    levelBg->addChild(m_levelUpLabel,1);
    
    m_progressBar = new ProgressBar("shopItemTiao1.png","shopItemTiao2.png");
    m_progressBar->setBarRight();
    m_progressBar->setPosition(itemBg->getContentSize().width * 0.29, itemBg->getContentSize().height * 0.18);
    addChild(m_progressBar);
    
    m_upgradeLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 20);
    m_upgradeLabel->setPosition(itemBg->getContentSize().width * 0.33, -itemBg->getContentSize().height * 0.23);
    addChild(m_upgradeLabel,1);
    
    Sprite * jinbi2 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi2->setPosition(itemBg->getContentSize().width * 0.4, -itemBg->getContentSize().height * 0.23);
    addChild(jinbi2);
}
void ShopGunItemScrollHeadler::initLockGunView()
{
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    
    Sprite * itemBg = Sprite::create(ImagePath("shopItemBg2.png"));
    addChild(itemBg);
    //
    string gunModelId = gun->getModelId();
    string gunIconStr = StringUtils::format("%s_grayicon.png",gunModelId.c_str());
    string gunNameStr = StringUtils::format("%s_name.png",gunModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(gunIconStr));
    icon->setPosition(icon->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
    addChild(icon);
    Sprite * lockIcon = Sprite::create(ImagePath("shopItemLockIcon.png"));
    lockIcon->setPosition(icon->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
    addChild(lockIcon);
    
    Sprite * iconName = Sprite::create(ImagePath(gunNameStr));
    iconName->setPosition(-itemBg->getContentSize().width * 0.25 + iconName->getContentSize().width * 1, itemBg->getContentSize().height * 0.18);
    addChild(iconName);
    
    m_unLockButton = MenuItemImage::create(ImagePath("shopItemButonUnclock.png"),
                                           ImagePath("shopItemButonUnclock.png"),
                                           CC_CALLBACK_1(ShopGunItemScrollHeadler::unLock, this));
    
    m_unLockButton->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
    Menu * buttonMenu = Menu::create(m_unLockButton, NULL);
    buttonMenu->setPosition(Point::ZERO);
    addChild(buttonMenu);
    Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
    unlockName->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
    addChild(unlockName);
    
    Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",gun->getUnlockGold()),
                                               "fonts/Arial Black.ttf",
                                               20);
    unlockLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.28);
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
            m_buyButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
            m_buyButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
        }else
        {
            m_buyButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_buyButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_buyButton->setEnabled(false);
        }
        if (gun->isDefaultGun() && bullets >= 12) {
            m_buyButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_buyButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_buyButton->setEnabled(false);
        }
        if (userGold >= upgradeGold && !gun->isMaxLevel())
        {
            m_upGradeButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
            m_upGradeButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
        }else
        {
            m_upGradeButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_upGradeButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_upGradeButton->setEnabled(false);
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
void ShopGunItemScrollHeadler::upGrade(Ref * pSender)
{
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
void ShopGunItemScrollHeadler::unLock(Ref * pSender)
{
    
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
void ShopGunItemScrollHeadler::buy(Ref * pSender)
{
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