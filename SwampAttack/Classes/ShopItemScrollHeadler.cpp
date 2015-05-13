//
//  ShopItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/12.
//
//

#include "ShopItemScrollHeadler.h"
#include "GunManager.h"
#include "GameUser.h"
#include "BaseUtil.h"


ShopItemScrollHeadler::ShopItemScrollHeadler(int index,int itemIndex):m_itemIndex(itemIndex)
{
    setIndex(index);
    
    switch (m_itemIndex) {
        
        case 0 :
        {
            initGunView();
        }
            break;
        case 1:
        {
            Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
            addChild(itemBg);
        }
            break;
        case 2:
        {
            Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
            addChild(itemBg);
        }
            break;
        case 3:
        {
            Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
            addChild(itemBg);
        }
            break;
        default:
            break;
    }
    
}
ShopItemScrollHeadler::~ShopItemScrollHeadler()
{
    
}
void ShopItemScrollHeadler::initGunView()
{
    removeAllChildrenWithCleanup(true);
    
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    if (gun->isUnlock())
    {
        Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
        addChild(itemBg);
        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
        iconBg->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, getPositionY());
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
                                            CC_CALLBACK_1(ShopItemScrollHeadler::buy, this));
        
        m_buyButton->setPosition(-itemBg->getContentSize().width * 0.03, -itemBg->getContentSize().height * 0.15);
        m_upGradeButton = MenuItemImage::create(ImagePath("shopItemButtonNormal.png"),
                                                ImagePath("shopItemButtonNormal.png"),
                                                CC_CALLBACK_1(ShopItemScrollHeadler::upGrade, this));
        
        m_upGradeButton->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        Menu * buttonMenu = Menu::create(m_buyButton,m_upGradeButton, NULL);
        buttonMenu->setPosition(Point::ZERO);
        addChild(buttonMenu);
        
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
                                                CC_CALLBACK_1(ShopItemScrollHeadler::unLock, this));
        
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
void ShopItemScrollHeadler::updateGunView()
{
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    
    if (gun->isUnlock())
    {
        int bulletPrice = gun->getBulletPrice();
        float level = gun->getStrengthenLevel();
        float limitLevel = gun->getLimitLevel();
        int upgradeGold = gun->getStrengthenGold();
        int bullets = gun->getBulletNum();
        
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
void ShopItemScrollHeadler::upGrade(Ref * pSender)
{
    switch (m_itemIndex)
    {
        case 0:
        {
            Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
            gun->addStrengthenLevel();
            updateGunView();
        }
            break;
        case 1:
        {
            
        }
            break;
        case 2:
        {
            
        }
            break;
        case 3:
        {
            
        }
            break;
    }
}
void ShopItemScrollHeadler::unLock(Ref * pSender)
{
    
}
void ShopItemScrollHeadler::buy(Ref * pSender)
{
    switch (m_itemIndex)
    {
        case 0:
        {
            Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
            gun->buyBullet();
            updateGunView();
        }
            break;
        case 1:
        {
            
        }
            break;
        case 2:
        {
            
        }
            break;
        case 3:
        {
            
        }
            break;
    }
}