//
//  ShopPropItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#include "ShopPropItemScrollHeadler.h"
//#include "GunManager.h"
#include "PropManager.h"
#include "DefenseBuildingManager.h"
#include "GameUser.h"


ShopPropItemScrollHeadler::ShopPropItemScrollHeadler(int index)
{
    setIndex(index);
    
    initDaojuView();
    
}
ShopPropItemScrollHeadler::~ShopPropItemScrollHeadler()
{
    //    log("shop item scroll headler remove");
}
void ShopPropItemScrollHeadler::setGameShopScene(GameShopScene *shopScene)
{
    m_shopScene = shopScene;
}
void ShopPropItemScrollHeadler::initDaojuView()
{
    removeAllChildrenWithCleanup(true);
    
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    setSubject(prop);
    if (prop->isUnlock())
    {
        Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
        addChild(itemBg);
        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
        iconBg->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
        addChild(iconBg);
        
        string propModelId = prop->getModelId();
        string propIconStr = StringUtils::format("%s_icon.png",propModelId.c_str());
        string propNameStr = StringUtils::format("%s_name.png",propModelId.c_str());
        Sprite * icon = Sprite::create(ImagePath(propIconStr));
        icon->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
        addChild(icon);
        
        Sprite * iconName = Sprite::create(ImagePath(propNameStr));
        iconName->setPosition(-itemBg->getContentSize().width * 0.25 + iconName->getContentSize().width * 1, itemBg->getContentSize().height * 0.18);
        addChild(iconName);
        
        m_buyButton = MenuItemImage::create(ImagePath("shopItemButtonNormal.png"),
                                            ImagePath("shopItemButtonNormal.png"),
                                            CC_CALLBACK_1(ShopPropItemScrollHeadler::buy, this));
        
        m_buyButton->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        Menu * buttonMenu = Menu::create(m_buyButton, NULL);
        buttonMenu->setPosition(Point::ZERO);
        addChild(buttonMenu);
        
        m_takeUpButton = MenuItemImage::create(ImagePath("shop_zhuanbei.png"),
                                               ImagePath("shop_zhuanbei.png"),
                                               CC_CALLBACK_1(ShopPropItemScrollHeadler::takeUp, this));
        
        m_takeUpButton->setPosition(itemBg->getContentSize().width * 0.5, 0);
        Menu * takeUpMenu = Menu::create(m_takeUpButton, NULL);
        takeUpMenu->setPosition(Point::ZERO);
        addChild(takeUpMenu);
        if (prop->isTakeUp())
        {
            m_takeUpButton->setVisible(false);
        }
        
        
        Sprite * buyLabel = Sprite::create(ImagePath("shopItemLabel2.png"));
        buyLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.1);
        addChild(buyLabel);
        
        string price = StringUtils::format("%d",prop->getPropPrice());
        m_buyLabel = Label::createWithTTF(price, "fonts/Arial Black.ttf", 20);
        m_buyLabel->setPosition(itemBg->getContentSize().width * 0.33, -itemBg->getContentSize().height * 0.25);
        addChild(m_buyLabel);
        m_bulletsLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 20);
        m_bulletsLabel->setPosition(- itemBg->getContentSize().width * 0.27, -itemBg->getContentSize().height * 0.25);
        addChild(m_bulletsLabel);
        m_bulletsLabel->setColor(Color3B(0, 0, 0));
        
        Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
        jinbi1->setPosition(itemBg->getContentSize().width * 0.4, -itemBg->getContentSize().height * 0.23);
        addChild(jinbi1);
        
    }else
    {
        Sprite * itemBg = Sprite::create(ImagePath("shopItemBg2.png"));
        addChild(itemBg);
        //
        string propModelId = prop->getModelId();
        string propIconStr = StringUtils::format("%s_grayicon.png",propModelId.c_str());
        string propNameStr = StringUtils::format("%s_name.png",propModelId.c_str());
        Sprite * icon = Sprite::create(ImagePath(propIconStr));
        icon->setPosition(icon->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
        addChild(icon);
        Sprite * lockIcon = Sprite::create(ImagePath("shopItemLockIcon.png"));
        lockIcon->setPosition(icon->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
        addChild(lockIcon);
        
        Sprite * iconName = Sprite::create(ImagePath(propNameStr));
        iconName->setPosition(-itemBg->getContentSize().width * 0.25 + iconName->getContentSize().width * 1, itemBg->getContentSize().height * 0.18);
        addChild(iconName);
        
        m_unLockButton = MenuItemImage::create(ImagePath("shopItemButonUnclock.png"),
                                               ImagePath("shopItemButonUnclock.png"),
                                               CC_CALLBACK_1(ShopPropItemScrollHeadler::unLock, this));
        
        m_unLockButton->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        Menu * buttonMenu = Menu::create(m_unLockButton, NULL);
        buttonMenu->setPosition(Point::ZERO);
        addChild(buttonMenu);
        Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
        unlockName->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        addChild(unlockName);
        
        Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",prop->getUnlockGold()),
                                                   "fonts/Arial Black.ttf",
                                                   20);
        unlockLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.28);
        addChild(unlockLabel);
    }
    
    updateDaojuView();
}
void ShopPropItemScrollHeadler::updateDaojuView()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    
    if (prop->isUnlock())
    {
        int propPrice = prop->getPropPrice();
        int propNum = prop->getNum();
        int userGold = GameUser::getInstance()->getUserGold();
        
        m_bulletsLabel->setString(StringUtils::format("%d",propNum));
        if (userGold >= propPrice)
        {
            m_buyButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
            m_buyButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonNormal.png")));
        }else
        {
            m_buyButton->setNormalImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
            m_buyButton->setSelectedImage(Sprite::create(ImagePath("shopItemButtonDisable.png")));
        }
    }
}
void ShopPropItemScrollHeadler::updateData()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    if (prop->isUnlock())
    {
        if (prop->isTakeUp())
        {
            m_takeUpButton->setVisible(false);
        }else
        {
            m_takeUpButton->setVisible(true);
        }
    }
}
void ShopPropItemScrollHeadler::upGrade(Ref * pSender)
{
    
}
void ShopPropItemScrollHeadler::unLock(Ref * pSender)
{
    
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    bool sec = prop->unlockProp();
    if (sec)
    {
        m_shopScene->updateGoldView();
        initDaojuView();
    }else
    {
        log("no enough money for unlock");
    }
}
void ShopPropItemScrollHeadler::buy(Ref * pSender)
{
    
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    bool sec = prop->buyProp();
    if (sec)
    {
        m_shopScene->updateGoldView();
        updateDaojuView();
    }else
    {
        
    }
}
void ShopPropItemScrollHeadler::takeUp(cocos2d::Ref *pSender)
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    PropManager::getInstance()->takeUpProp(prop->getId());
    
}