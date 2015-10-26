//
//  ShopBuildingItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#include "ShopBuildingItemScrollHeadler.h"
//#include "GunManager.h"
//#include "PropManager.h"
#include "DefenseBuildingManager.h"
#include "GameUser.h"
#include "GameShowLevelupLayer.h"
#include "GameSprite.h"
#include "GameShowDiscLayer.h"
#include "BaseUtil.h"


ShopBuildingItemScrollHeadler::ShopBuildingItemScrollHeadler(int index)
{
    setIndex(index);
    
    _G_U->attach(this);
    initDefenseView();
    
    
}
ShopBuildingItemScrollHeadler::~ShopBuildingItemScrollHeadler()
{
    _G_U->detach(this);
    //    log("shop item scroll headler remove");
}
void ShopBuildingItemScrollHeadler::setGameShopScene(GameShopScene *shopScene)
{
    m_shopScene = shopScene;
}
void ShopBuildingItemScrollHeadler::initDefenseView()
{
    removeAllChildrenWithCleanup(true);
    
    DefenseBuilding * building = DefenseBuildingManager::getInstance()->getBuildingByIndex(m_index);
    if (building->isUnlock())
    {
        Sprite * itemBg = Sprite::create(ImagePath("shopItemBg1.png"));
        addChild(itemBg);
        Size itemBgSize = itemBg->getContentSize();
        
        m_iconBg = new GameSprite(ImagePath("shopItemIconBg.png"));
        m_iconBg->autorelease();
        m_iconBg->m_touchMeCall = CC_CALLBACK_2(ShopBuildingItemScrollHeadler::showDiscView, this);
        
//        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
        m_iconBg->setPosition(- itemBgSize.width * 0.35,
                            0);
        addChild(m_iconBg);
        
        Size iconBgSize = m_iconBg->getContentSize();
        
        Sprite * biaoSign = Sprite::create(ImagePath("shop_icon_sign.png"));
        biaoSign->setPosition(iconBgSize.width * 0.25,
                              iconBgSize.height * 0.71);
        m_iconBg->addChild(biaoSign);
        
        string buildingModelId = building->getModelId();
        string buildingIconStr = StringUtils::format("%s_icon.png",buildingModelId.c_str());
        string buildingNameStr = StringUtils::format("%s_name.png",buildingModelId.c_str());
        Sprite * icon = Sprite::create(ImagePath(buildingIconStr));
        icon->setPosition(iconBgSize.width * 0.5,
                          iconBgSize.height * 0.5);
        icon->setScale(0.85);
        m_iconBg->addChild(icon,1);
        
        Sprite * iconName = Sprite::create(ImagePath(buildingNameStr));
        iconName->setPosition(-itemBgSize.width * 0.25
                              + iconName->getContentSize().width * 1,
                              itemBgSize.height * 0.2);
        addChild(iconName);
        
        m_upGradeButton = new GameSprite(ImagePath("shopItemButtonNormal.png"));
        m_upGradeButton->m_touchMeCall = CC_CALLBACK_2(ShopBuildingItemScrollHeadler::upGrade, this);
        m_upGradeButton->setPosition(itemBgSize.width * 0.29,
                                     -itemBgSize.height * 0.15);
        m_upGradeButton->autorelease();
        addChild(m_upGradeButton);
        
        Size upGradeButtonSize = m_upGradeButton->getContentSize();
        
        Label * upgradeLabel = Label::createWithTTF("LEVEL UP", "fonts/Arial Black.ttf", 30);
        upgradeLabel->setPosition(upGradeButtonSize.width * 0.5,
                                  upGradeButtonSize.height * 0.73);
        upgradeLabel->enableOutline(Color4B(0, 0, 0, 255),3);
        upgradeLabel->setAdditionalKerning(-3);
        m_upGradeButton->addChild(upgradeLabel);
//        Sprite * upgradeLabel = Sprite::create(ImagePath("shopItemLabel1.png"));
//        upgradeLabel->setPosition(itemBgSize.width * 0.29,
//                                  -itemBgSize.height * 0.04);
//        addChild(upgradeLabel);
        
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
        Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
        jinbi1->setPosition(upGradeButtonSize.width * 0.85,
                            upGradeButtonSize.height * 0.35);
        jinbi1->setScale(0.75);
        m_upGradeButton->addChild(jinbi1);
    }else
    {
        Sprite * itemBg = Sprite::create(ImagePath("shopItemBg2.png"));
        addChild(itemBg);
        Size itemBgSize = itemBg->getContentSize();
        //
        string buildingModelId = building->getModelId();
        string buildingIconStr = StringUtils::format("%s_grayicon.png",buildingModelId.c_str());
        string buildingNameStr = StringUtils::format("%s_name.png",buildingModelId.c_str());
        Sprite * icon = Sprite::create(ImagePath(buildingIconStr));
        icon->setPosition(- itemBgSize.width * 0.35,
                          0);
        addChild(icon);
        Sprite * lockIcon = Sprite::create(ImagePath("shopItemLockIcon.png"));
        lockIcon->setPosition(- itemBgSize.width * 0.3,
                              - itemBgSize.height * 0.18);
        addChild(lockIcon);
        
        Sprite * iconName = Sprite::create(ImagePath(buildingNameStr));
        iconName->setPosition(-itemBgSize.width * 0.25
                              + iconName->getContentSize().width * 1,
                              itemBgSize.height * 0.2);
        addChild(iconName);
        
        Label * m_text = Label::createWithTTF(building->getUnlockStr(), FontPath, 30);
        m_text->setLineHeight(35);
        m_text->setDimensions(itemBgSize.width * 0.3, itemBgSize.height * 0.2);
        m_text->setPosition(-itemBgSize.width * 0.028,
                            -itemBgSize.height * 0.18);
        addChild(m_text);
        //
        m_unLockButton = new GameSprite(ImagePath("shopItemButonUnclock.png"));
        m_unLockButton->m_touchMeCall = CC_CALLBACK_2(ShopBuildingItemScrollHeadler::unLock, this);
        m_unLockButton->setPosition(itemBgSize.width * 0.29,
                                    -itemBgSize.height * 0.15);
        m_unLockButton->autorelease();
        addChild(m_unLockButton);
        
        Size unlockButtonSize = m_unLockButton->getContentSize();
        
        Label * unlockName = Label::createWithTTF("UNLOCK", "fonts/Arial Black.ttf", 30);
        unlockName->setPosition(unlockButtonSize.width * 0.5,
                                unlockButtonSize.height * 0.68);
        unlockName->enableOutline(Color4B(0, 0, 0, 255),3);
        unlockName->setAdditionalKerning(-3);
        m_unLockButton->addChild(unlockName);
//        Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
//        unlockName->setPosition(itemBgSize.width * 0.29,
//                                -itemBgSize.height * 0.15);
//        addChild(unlockName);
        
        Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",building->getUnlockGold()),
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
    
    updateDefenseView();
}
void ShopBuildingItemScrollHeadler::updateDefenseView()
{
    DefenseBuilding * building = DefenseBuildingManager::getInstance()->getBuildingByIndex(m_index);
    
    if (building->isUnlock())
    {
        float level = building->getStrengthLevel();
        float limitLevel = building->getLimitLevel();
        int upgradeGold = building->getStrengthGold();
        
        if (building->isMaxLevel())
        {
            m_upgradeLabel->setString("MAX");
        }else
        {
            m_upgradeLabel->setString(StringUtils::format("%d",upgradeGold));
        }
        
        m_levelUpLabel->setString(StringUtils::format("LV.%d",(int)level));
        m_progressBar->updatePercent(level/limitLevel * 100);
        
        int userGold = GameUser::getInstance()->getUserGold();
        if (userGold >= upgradeGold && !building->isMaxLevel())
        {
            m_upGradeButton->setEnabled(true,ImagePath("shopItemButtonNormal.png"));
        }else
        {
            m_upGradeButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
    }
    
}
void ShopBuildingItemScrollHeadler::setHealderSelect()
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
                                       CallFuncN::create(CC_CALLBACK_1(ShopBuildingItemScrollHeadler::guangEnd, this)),
                                       NULL));
}
void ShopBuildingItemScrollHeadler::guangEnd(cocos2d::Node *pSender)
{
    pSender->stopAllActions();
    pSender->removeFromParentAndCleanup(true);
}
void ShopBuildingItemScrollHeadler::updateData()
{
    updateDefenseView();
}
void ShopBuildingItemScrollHeadler::upGrade(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
    DefenseBuilding * building = DefenseBuildingManager::getInstance()->getBuildingByIndex(m_index);
    int upgradeGold = building->getStrengthGold();
    int userGold = _G_U->getUserGold();
    if (userGold >= upgradeGold)
    {
        SimpleAudioEngine::getInstance()->playEffect(MusicPath("propUpgrade.mp3").c_str());
        userGold -= upgradeGold;
        
//        m_shopScene->updateUserData();
        building->addStrengthenLevel();
//        updateDefenseView();
        _G_U->setUserGold(userGold);
        GameShowLevelupLayer * showLayer = new GameShowLevelupLayer(building->getModelId());
        showLayer->autorelease();
        m_shopScene->addChild(showLayer,10);
    }else
    {
        
    }
}
void ShopBuildingItemScrollHeadler::unLock(Touch * touch, Event * event)
{
    
    DefenseBuilding * building = DefenseBuildingManager::getInstance()->getBuildingByIndex(m_index);
    int unlockGold = building->getUnlockGold();
    int userGold = _G_U->getUserGold();
    if (userGold >= unlockGold)
    {
        SimpleAudioEngine::getInstance()->playEffect(MusicPath("buttonPress.mp3").c_str());
        
        userGold -= unlockGold;
        _G_U->setUserGold(userGold);
//        m_shopScene->updateUserData();
        building->unlockBuilding();
        initDefenseView();
    }else
    {
        log("no enough money for unlock");
    }
}
void ShopBuildingItemScrollHeadler::buy(Touch * touch, Event * event)
{
    
}
void ShopBuildingItemScrollHeadler::showDiscView(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Sprite * icon = (Sprite *) event->getCurrentTarget();
    Vec2 iconPoint = convertToWorldSpace(icon->getPosition());
    
    DefenseBuilding * building = DefenseBuildingManager::getInstance()->getBuildingByIndex(m_index);
    std::string name = building->getModelId();
    std::string disc = building->getDefenceDescription();
    GameShowDiscLayer * showLayer = new GameShowDiscLayer(name,disc,iconPoint);
    showLayer->autorelease();
    m_shopScene->addChild(showLayer);
    
}