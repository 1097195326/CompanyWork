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
#include "AlertTextTool.h"
#include "BaseUtil.h"

ShopGunItemScrollHeadler::ShopGunItemScrollHeadler(int index)
{
    setIndex(index);
    _G_U->attach(this);
    initGunView();
    
}
ShopGunItemScrollHeadler::~ShopGunItemScrollHeadler()
{
    _G_U->detach(this);
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
    
    m_iconBg = new GameSprite(ImagePath("shopItemIconBg.png"));
    m_iconBg->autorelease();
    m_iconBg->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::showDiscView, this);
    
    //        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
    m_iconBg->setPosition(- itemBgSize.width * 0.35,
                        0);
    addChild(m_iconBg);
    
    Size iconBgSize = m_iconBg->getContentSize();
    
    Sprite * biaoSign = Sprite::create(ImagePath("shop_icon_sign.png"));
    biaoSign->setPosition(iconBgSize.width * 0.25,
                          iconBgSize.height * 0.71);
    m_iconBg->addChild(biaoSign);
    
    string gunModelId = gun->getModelId();
    string gunIconStr = StringUtils::format("%s_icon.png",gunModelId.c_str());
    string gunNameStr = StringUtils::format("%s_name.png",gunModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(gunIconStr));
    icon->setPosition(iconBgSize.width * 0.5,
                      iconBgSize.height * 0.5);
    icon->setScale(0.85);
    m_iconBg->addChild(icon,1);
    
    Sprite * iconName = Sprite::create(ImagePath(gunNameStr));
//    Label * iconName = Label::createWithTTF(gun->getWeaponName(), "fonts/Arial Black.ttf", 25);
    iconName->setPosition(-itemBgSize.width * 0.25
                          + iconName->getContentSize().width * 1,
                          itemBgSize.height * 0.2);
//    iconName->enableOutline(Color4B(0, 0, 0, 255),2);
//    iconName->setAdditionalKerning(-3);
    addChild(iconName);
    
    m_upGradeButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
    m_upGradeButton->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::upGrade, this);
    m_upGradeButton->setPosition(itemBgSize.width * 0.29,
                                 -itemBgSize.height * 0.15);
    m_upGradeButton->autorelease();
    addChild(m_upGradeButton);
    
    Size upGradeButtonSize = m_upGradeButton->getContentSize();
    
    if (gun->getWeaponType() != 1)
    {
        m_buyButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
        m_buyButton->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::buy, this);
        m_buyButton->setPosition(-itemBgSize.width * 0.03,
                                 -itemBgSize.height * 0.15);
        m_buyButton->autorelease();
        addChild(m_buyButton);
        
        Size buyButtonSize = m_buyButton->getContentSize();
        
        m_bulletsLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 25);
        m_bulletsLabel->enableOutline(Color4B(0, 0, 0, 255),2);
        m_bulletsLabel->setPosition(iconBgSize.width * 0.62,
                                    iconBgSize.height * 0.25);
        m_bulletsLabel->setAdditionalKerning(-3);
        m_iconBg->addChild(m_bulletsLabel,1);
        Sprite * bulletIcon = Sprite::create(ImagePath("shop_bullet_icon.png"));
        bulletIcon->setPosition(iconBgSize.width * 0.81  ,
                                iconBgSize.height * 0.25);
        m_iconBg->addChild(bulletIcon,1);
        
        Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
        jinbi1->setPosition(buyButtonSize.width * 0.85,
                            buyButtonSize.height * 0.35);
        jinbi1->setScale(0.75);
        m_buyButton->addChild(jinbi1,1);
        m_buyLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 30);
        m_buyLabel->enableOutline(Color4B(0, 0, 0, 255),3);
        m_buyLabel->setPosition(buyButtonSize.width * 0.55,
                                buyButtonSize.height * 0.35);
        m_buyLabel->setAdditionalKerning(-3);
        m_buyButton->addChild(m_buyLabel,1);
        //    Sprite * buyLabel = Sprite::create(ImagePath("shopItemLabel2.png"));
        Label * buyLabel = Label::createWithTTF("AMMO", "fonts/Arial Black.ttf", 30);
        buyLabel->setPosition(buyButtonSize.width * 0.5,
                              buyButtonSize.height * 0.73);
        buyLabel->enableOutline(Color4B(0, 0, 0, 255),3);
        buyLabel->setAdditionalKerning(-3);
        m_buyButton->addChild(buyLabel,1);
    }
    
    
    m_takeUpButton = MenuItemImage::create(ImagePath("shop_zhuanbei.png"),
                                           ImagePath("shop_zhuanbei.png"),
                                           CC_CALLBACK_1(ShopGunItemScrollHeadler::takeUp, this));
    
    m_takeUpButton->setPosition(itemBgSize.width * 0.5,
                                -itemBgSize.height * 0.1);
    Menu * takeUpMenu = Menu::create(m_takeUpButton, NULL);
    takeUpMenu->setPosition(Point::ZERO);
    addChild(takeUpMenu);
    if (gun->isTakeUp())
    {
        m_takeUpButton->setVisible(false);
    }
//    Sprite * upgradeLabel = Sprite::create(ImagePath("shopItemLabel1.png"));
    Label * upgradeLabel = Label::createWithTTF("LEVEL UP", "fonts/Arial Black.ttf", 30);
    upgradeLabel->setPosition(upGradeButtonSize.width * 0.5,
                              upGradeButtonSize.height * 0.73);
    upgradeLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    upgradeLabel->setAdditionalKerning(-3);
    m_upGradeButton->addChild(upgradeLabel);
    
    m_progressBar = new ProgressBar("shopItemTiao1.png","shopItemTiao2.png");
    m_progressBar->autorelease();
    m_progressBar->setBarRight();
    m_progressBar->setPosition(itemBgSize.width * 0.32,
                               itemBgSize.height * 0.18);
    addChild(m_progressBar);
    
    m_levelUpLabel = Label::createWithTTF("LV", "fonts/Arial Black.ttf", 24);
    m_levelUpLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_levelUpLabel->setPosition(itemBgSize.width * 0.16,
                                itemBgSize.height * 0.18);
    m_levelUpLabel->setAdditionalKerning(-3);
    addChild(m_levelUpLabel,1);
    
    m_upgradeLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 30);
    m_upgradeLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    m_upgradeLabel->setPosition(upGradeButtonSize.width * 0.55,
                                upGradeButtonSize.height * 0.35);
    m_upgradeLabel->setAdditionalKerning(-3);
    m_upGradeButton->addChild(m_upgradeLabel,1);
    
    Sprite * jinbi2 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi2->setPosition(upGradeButtonSize.width * 0.85,
                        upGradeButtonSize.height * 0.35);
    jinbi2->setScale(0.75);
    m_upGradeButton->addChild(jinbi2);
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
    
    Label * m_text = Label::createWithTTF(gun->getUnlockStr(), FontPath, 30);
    m_text->setLineHeight(35);
    m_text->setDimensions(itemBgSize.width * 0.3, itemBgSize.height * 0.2);
    m_text->setPosition(-itemBgSize.width * 0.028,
                        -itemBgSize.height * 0.18);
    addChild(m_text);
    
    m_unLockButton = new GameSprite(ImagePath("shopItemButonUnclock.png"));
    m_unLockButton->setPosition(itemBgSize.width * 0.29,
                                -itemBgSize.height * 0.15);
    m_unLockButton->m_touchMeCall = CC_CALLBACK_2(ShopGunItemScrollHeadler::unLock, this);
    m_unLockButton->autorelease();
    addChild(m_unLockButton);
    
    Size unlockButtonSize = m_unLockButton->getContentSize();
    
    Label * unlockName = Label::createWithTTF("UNLOCK", "fonts/Arial Black.ttf", 30);
    unlockName->setPosition(unlockButtonSize.width * 0.5,
                            unlockButtonSize.height * 0.68);
    unlockName->enableOutline(Color4B(0, 0, 0, 255),3);
    unlockName->setAdditionalKerning(-3);
    m_unLockButton->addChild(unlockName);
//    Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
//    unlockName->setPosition(itemBgSize.width * 0.29,
//                            -itemBgSize.height * 0.15);
//    addChild(unlockName);
    
    Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",gun->getUnlockGold()),
                                               "fonts/Arial Black.ttf",
                                               30);
    unlockLabel->setPosition(unlockButtonSize.width * 0.5,
                             unlockButtonSize.height * 0.35);
    unlockLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    unlockLabel->setAdditionalKerning(-3);
    m_unLockButton->addChild(unlockLabel);
    Sprite * jinbi2 = Sprite::create(ImagePath("jinbi_icon.png"));
    jinbi2->setPosition(unlockButtonSize.width * 0.85,
                        unlockButtonSize.height * 0.35);
    jinbi2->setScale(0.75);
    m_unLockButton->addChild(jinbi2);
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
        if (gun->getWeaponType() != 1)
        {
            m_buyLabel->setString(StringUtils::format("%d",bulletPrice));
            m_bulletsLabel->setString(StringUtils::format("%d",bullets));
        }
        
        int userGold = GameUser::getInstance()->getUserGold();
        
        if (userGold >= bulletPrice)
        {
            if (gun->getWeaponType() != 1)
            {
                m_buyButton->setEnabled(true,ImagePath("shopItemButtonNormal.png"));
            }
        }else
        {
            if (gun->getWeaponType() != 1)
            {
                m_buyButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
            }
        }
        if (gun->isDefaultGun() && bullets >= 12)
        {
            if (gun->getWeaponType() != 1)
            {
                m_buyButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
            }
        }
        if (userGold >= upgradeGold && !gun->isMaxLevel())
        {
            m_upGradeButton->setEnabled(true,ImagePath("shopItemButtonNormal.png"));
        }else
        {
            m_upGradeButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
    }else
    {
        
    }
    
    
}
void ShopGunItemScrollHeadler::setHealderSelect()
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile(ImagePath("texiao2.plist"));
    
    Action * guangAc = RepeatForever::create(BaseUtil::makeAnimateWithNameAndIndex("item_flash", 4));
    Sprite * texiao = Sprite::create();
    Sprite * guang = Sprite::create();
    texiao->addChild(guang);
    guang->runAction(guangAc);
    m_iconBg->addChild(texiao);
    Size iconBgSize = m_iconBg->getContentSize();
    texiao->setPosition(iconBgSize.width * 0.5, iconBgSize.height * 0.5);
    texiao->setScale(1.5);
    texiao->runAction(Sequence::create(DelayTime::create(1),
                                       FadeOut::create(0.3),
                                       CallFuncN::create(CC_CALLBACK_1(ShopGunItemScrollHeadler::guangEnd, this)),
                                       NULL));
    
}
void ShopGunItemScrollHeadler::guangEnd(cocos2d::Node *pSender)
{
    pSender->stopAllActions();
    pSender->removeAllChildrenWithCleanup(true);
    pSender->removeFromParentAndCleanup(true);
}
void ShopGunItemScrollHeadler::updateData()
{
//    log("gun scroll headler update data");
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
    updateGunView();
}
void ShopGunItemScrollHeadler::upGrade(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    bool sec = gun->addStrengthenLevel();
    if (sec)
    {
        SimpleAudioEngine::getInstance()->playEffect(MusicPath("propUpgrade.mp3").c_str());
//        m_shopScene->updateUserData();
//        updateGunView();
        GameShowLevelupLayer * showLayer = new GameShowLevelupLayer(gun->getModelId());
        showLayer->autorelease();
        m_shopScene->addChild(showLayer,10);
    }else
    {
        AlertText(goldNoEnough, 40);
    }
}
void ShopGunItemScrollHeadler::unLock(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    bool sec = gun->unlockGun();
    if (sec)
    {
//        m_shopScene->updateUserData();
        initGunView();
    }else
    {
//        log("no enough money for unlock");
        AlertText(goldNoEnough, 40);
    }
}
void ShopGunItemScrollHeadler::buy(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    Gun * gun = GunManager::getInstance()->getGunByIndex(m_index);
    bool sec = gun->buyBullet();
    if (sec)
    {
//        m_shopScene->updateUserData();
//        updateGunView();
    }else
    {
        AlertText(goldNoEnough, 40);
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