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
//#include "DefenseBuildingManager.h"
#include "GameUser.h"
#include "GameSprite.h"
#include "GameShowDiscLayer.h"
#include "GameShowLevelupLayer.h"

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
        initUnlockView();
    }else
    {
        initLockView();
    }
    
    updateDaojuView();
}
void ShopPropItemScrollHeadler::initUnlockView()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    
    Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
    addChild(itemBg);
    
    GameSprite * iconBg = new GameSprite(ImagePath("shopItemIconBg.png"));
    iconBg->autorelease();
    iconBg->m_touchMeCall = CC_CALLBACK_2(ShopPropItemScrollHeadler::showDiscView, this);
    
    //        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
    iconBg->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
    addChild(iconBg);
    
    string propModelId = prop->getModelId();
    string propIconStr = StringUtils::format("%s_icon.png",propModelId.c_str());
    string propNameStr = StringUtils::format("%s_name.png",propModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(propIconStr));
    icon->setPosition(iconBg->getContentSize().width * 0.75
                      - itemBg->getContentSize().width * 0.5,
                      0);
    addChild(icon);
    
    Sprite * iconName = Sprite::create(ImagePath(propNameStr));
    iconName->setPosition(-itemBg->getContentSize().width * 0.25
                          + iconName->getContentSize().width * 1,
                          itemBg->getContentSize().height * 0.18);
    addChild(iconName);
    
    m_upGradeButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
    m_upGradeButton->m_touchMeCall = CC_CALLBACK_2(ShopPropItemScrollHeadler::upGrade, this);
    m_upGradeButton->setPosition(itemBg->getContentSize().width * 0.29,
                                 -itemBg->getContentSize().height * 0.15);
    m_upGradeButton->autorelease();
    addChild(m_upGradeButton);
    
    m_buyButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
    m_buyButton->m_touchMeCall = CC_CALLBACK_2(ShopPropItemScrollHeadler::buy, this);
    m_buyButton->setPosition(-itemBg->getContentSize().width * 0.03,
                             -itemBg->getContentSize().height * 0.15);
    m_buyButton->autorelease();
    addChild(m_buyButton);
    
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
    
    m_bulletsLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 20);
    m_bulletsLabel->enableOutline(Color4B(0, 0, 0, 255),2);
    m_bulletsLabel->setPosition(- itemBg->getContentSize().width * 0.3,
                                -itemBg->getContentSize().height * 0.25);
    addChild(m_bulletsLabel,1);
    Sprite * bulletIcon = Sprite::create(ImagePath("shop_bullet_icon.png"));
    bulletIcon->setPosition(- itemBg->getContentSize().width * 0.26,
                            -itemBg->getContentSize().height * 0.25);
    addChild(bulletIcon,1);
    
    Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi1->setPosition(itemBg->getContentSize().width * 0.08,
                        -itemBg->getContentSize().height * 0.23);
    jinbi1->setScale(0.8);
    addChild(jinbi1,1);
    string price = StringUtils::format("%d",prop->getPropPrice());
    m_buyLabel = Label::createWithTTF(price, "fonts/Arial Black.ttf", 20);
    m_buyLabel->enableOutline(Color4B(0, 0, 0, 255),2);
    m_buyLabel->setPosition(itemBg->getContentSize().width * 0.02,
                            -itemBg->getContentSize().height * 0.23);
    addChild(m_buyLabel,1);
    Sprite * buyLabel = Sprite::create(ImagePath("shopItemLabel2.png"));
    buyLabel->setPosition(-itemBg->getContentSize().width * 0.03,
                          -itemBg->getContentSize().height * 0.04);
    addChild(buyLabel,1);
    
    //--
    Sprite * upgradeLabel = Sprite::create(ImagePath("shopItemLabel1.png"));
    upgradeLabel->setPosition(itemBg->getContentSize().width * 0.29,
                              -itemBg->getContentSize().height * 0.04);
    addChild(upgradeLabel);
    
    m_progressBar = new ProgressBar("shopItemTiao1.png","shopItemTiao2.png");
    m_progressBar->setBarRight();
    m_progressBar->setPosition(itemBg->getContentSize().width * 0.29,
                               itemBg->getContentSize().height * 0.18);
    addChild(m_progressBar);
    
    Sprite * levelBg = Sprite::create(ImagePath("shopItemLevelBg.png"));
    levelBg->setPosition(itemBg->getContentSize().width * 0.13,
                         itemBg->getContentSize().height * 0.18);
    addChild(levelBg);
    m_levelUpLabel = Label::createWithTTF("LV", "fonts/Arial Black.ttf", 20);
    m_levelUpLabel->enableOutline(Color4B(0, 0, 0, 255),2);
    m_levelUpLabel->setPosition(levelBg->getContentSize().width * 0.5,
                                levelBg->getContentSize().height * 0.5);
    levelBg->addChild(m_levelUpLabel,1);
    
    m_upgradeLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 20);
    m_upgradeLabel->enableOutline(Color4B(0, 0, 0, 255),2);
    m_upgradeLabel->setPosition(itemBg->getContentSize().width * 0.33,
                                -itemBg->getContentSize().height * 0.23);
    addChild(m_upgradeLabel,1);
    
    Sprite * jinbi2 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi2->setPosition(itemBg->getContentSize().width * 0.4,
                        -itemBg->getContentSize().height * 0.23);
    jinbi2->setScale(0.8);
    addChild(jinbi2);
}
void ShopPropItemScrollHeadler::initLockView()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    
    Sprite * itemBg = Sprite::create(ImagePath("shopItemBg2.png"));
    addChild(itemBg);
    //
    string propModelId = prop->getModelId();
    string propIconStr = StringUtils::format("%s_grayicon.png",propModelId.c_str());
    string propNameStr = StringUtils::format("%s_name.png",propModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(propIconStr));
    icon->setPosition(icon->getContentSize().width * 0.75
                      - itemBg->getContentSize().width * 0.5,
                      0);
    addChild(icon);
    Sprite * lockIcon = Sprite::create(ImagePath("shopItemLockIcon.png"));
    lockIcon->setPosition(- itemBg->getContentSize().width * 0.3,
                          - itemBg->getContentSize().height * 0.18);
    addChild(lockIcon);
    
    Sprite * iconName = Sprite::create(ImagePath(propNameStr));
    iconName->setPosition(-itemBg->getContentSize().width * 0.25
                          + iconName->getContentSize().width * 1,
                          itemBg->getContentSize().height * 0.18);
    addChild(iconName);
    
    m_unLockButton = new GameSprite(ImagePath("shopItemButonUnclock.png"));
    m_unLockButton->m_touchMeCall =CC_CALLBACK_2(ShopPropItemScrollHeadler::unLock, this);
    m_unLockButton->autorelease();
    m_unLockButton->setPosition(itemBg->getContentSize().width * 0.29,
                                -itemBg->getContentSize().height * 0.15);
    addChild(m_unLockButton);
    
    Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
    unlockName->setPosition(itemBg->getContentSize().width * 0.29,
                            -itemBg->getContentSize().height * 0.15);
    addChild(unlockName);
    
    Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",prop->getUnlockGold()),
                                               "fonts/Arial Black.ttf",
                                               20);
    unlockLabel->setPosition(itemBg->getContentSize().width * 0.29,
                             -itemBg->getContentSize().height * 0.28);
    addChild(unlockLabel);
}
void ShopPropItemScrollHeadler::updateDaojuView()
{
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    
    if (prop->isUnlock())
    {
        int propPrice = prop->getPropPrice();
        int propNum = prop->getNum();
        float level = prop->getStrengthenLevel();
        float limitLevel = prop->getLimitLevel();
        int upgradeGold = prop->getStrengthenGold();
        
        int userGold = GameUser::getInstance()->getUserGold();
        
        if (prop->isMaxLevel())
        {
            m_upgradeLabel->setString("MAX");
        }else
        {
            m_upgradeLabel->setString(StringUtils::format("%d",upgradeGold));
        }
        m_levelUpLabel->setString(StringUtils::format("LV.%d",(int)level));
        m_progressBar->updatePercent(level/limitLevel * 100);
        m_bulletsLabel->setString(StringUtils::format("%d",propNum));
        
        if (userGold >= propPrice)
        {
            m_buyButton->setEnabled(true);
        }else
        {
            m_buyButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
        if (userGold >= upgradeGold && !prop->isMaxLevel())
        {
            m_upGradeButton->setEnabled(true);
        }else
        {
            m_upGradeButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
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
void ShopPropItemScrollHeadler::upGrade(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    bool sec = prop->addStrengthenLevel();
    if (sec)
    {
        m_shopScene->updateGoldView();
        updateDaojuView();
        GameShowLevelupLayer * showLayer = new GameShowLevelupLayer(prop->getModelId());
        showLayer->autorelease();
        m_shopScene->addChild(showLayer);
    }else
    {
        
    }
}
void ShopPropItemScrollHeadler::unLock(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
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
void ShopPropItemScrollHeadler::buy(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
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
void ShopPropItemScrollHeadler::showDiscView(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Sprite * icon = (Sprite *) event->getCurrentTarget();
    Vec2 iconPoint = convertToWorldSpace(icon->getPosition());
    
    Prop * prop = PropManager::getInstance()->getPropByIndex(m_index);
    std::string name = prop->getModelId();
    std::string disc = prop->getItemDestription();
    GameShowDiscLayer * showLayer = new GameShowDiscLayer(name,disc,iconPoint);
    showLayer->autorelease();
    m_shopScene->addChild(showLayer);
    
}
