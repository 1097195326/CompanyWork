//
//  ShopGunItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#include "ShopGunItemScrollHeadler.h"
#include "GunManager.h"
#include "PropManager.h"
#include "DefenseBuildingManager.h"
#include "GameUser.h"


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
        Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
        addChild(itemBg);
        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
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
        
        m_buyButton = MenuItemImage::create(ImagePath("shopItemButtonNormal.png"),
                                            ImagePath("shopItemButtonNormal.png"),
                                            CC_CALLBACK_1(ShopGunItemScrollHeadler::buy, this));
        
        m_buyButton->setPosition(-itemBg->getContentSize().width * 0.03, -itemBg->getContentSize().height * 0.15);
        m_upGradeButton = MenuItemImage::create(ImagePath("shopItemButtonNormal.png"),
                                                ImagePath("shopItemButtonNormal.png"),
                                                CC_CALLBACK_1(ShopGunItemScrollHeadler::upGrade, this));
        
        m_upGradeButton->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        Menu * buttonMenu = Menu::create(m_buyButton,m_upGradeButton, NULL);
        buttonMenu->setPosition(Point::ZERO);
        addChild(buttonMenu);
        
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
        
        Sprite * buyLabel = Sprite::create(ImagePath("shopItemLabel2.png"));
        buyLabel->setPosition(-itemBg->getContentSize().width * 0.03, -itemBg->getContentSize().height * 0.15);
        addChild(buyLabel);
        Sprite * upgradeLabel = Sprite::create(ImagePath("shopItemLabel1.png"));
        upgradeLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        addChild(upgradeLabel);
        
        m_progressBar = new ProgressBar("shopItemTiao1.png","shopItemTiao2.png");
        m_progressBar->setBarRight();
        m_progressBar->setPosition(itemBg->getContentSize().width * 0.29, itemBg->getContentSize().height * 0.18);
        addChild(m_progressBar);
        m_buyLabel = Label::createWithTTF("", "fonts/American Typewriter.ttf", 20);
        m_buyLabel->setPosition(-itemBg->getContentSize().width * 0.01, -itemBg->getContentSize().height * 0.28);
        addChild(m_buyLabel);
        m_upgradeLabel = Label::createWithTTF("", "fonts/American Typewriter.ttf", 20);
        m_upgradeLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.28);
        addChild(m_upgradeLabel);
        m_bulletsLabel = Label::createWithTTF("", "fonts/American Typewriter.ttf", 20);
        m_bulletsLabel->setPosition(- itemBg->getContentSize().width * 0.3, -itemBg->getContentSize().height * 0.25);
        addChild(m_bulletsLabel);
    }else
    {
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
                                                   "fonts/American Typewriter.ttf",
                                                   20);
        unlockLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.28);
        addChild(unlockLabel);
    }
    
    updateGunView();
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
        
        m_buyLabel->setString(StringUtils::format("%d",bulletPrice));
        m_upgradeLabel->setString(StringUtils::format("%d",upgradeGold));
        m_progressBar->updatePercent(level/limitLevel * 100);
        m_bulletsLabel->setString(StringUtils::format("%d",bullets));
        
        int userGold = GameUser::getInstance()->getUserGold();
        if (userGold >= upgradeGold)
        {
            m_upGradeButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
            m_upGradeButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
        }else
        {
            m_upGradeButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_upGradeButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
        }
        if (userGold >= bulletPrice)
        {
            m_buyButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
            m_buyButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
        }else
        {
            m_buyButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_buyButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
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