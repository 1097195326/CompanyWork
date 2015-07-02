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

ShopBuildingItemScrollHeadler::ShopBuildingItemScrollHeadler(int index)
{
    setIndex(index);
    
    
    initDefenseView();
    
    
}
ShopBuildingItemScrollHeadler::~ShopBuildingItemScrollHeadler()
{
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
        
        GameSprite * iconBg = new GameSprite(ImagePath("shopItemIconBg.png"));
        iconBg->autorelease();
        iconBg->m_touchMeCall = CC_CALLBACK_2(ShopBuildingItemScrollHeadler::showDiscView, this);
        
//        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
        iconBg->setPosition(- itemBgSize.width * 0.35,
                            0);
        addChild(iconBg);
        
        Sprite * biaoSign = Sprite::create(ImagePath("shop_icon_sign.png"));
        biaoSign->setPosition(- itemBgSize.width * 0.41,
                              itemBgSize.height * 0.2);
        addChild(biaoSign);
        
        string buildingModelId = building->getModelId();
        string buildingIconStr = StringUtils::format("%s_icon.png",buildingModelId.c_str());
        string buildingNameStr = StringUtils::format("%s_name.png",buildingModelId.c_str());
        Sprite * icon = Sprite::create(ImagePath(buildingIconStr));
        icon->setPosition(- itemBgSize.width * 0.35, 0);
        addChild(icon);
        
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
        addChild(m_upgradeLabel);
        Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
        jinbi1->setPosition(itemBgSize.width * 0.4,
                            -itemBgSize.height * 0.23);
        jinbi1->setScale(0.8);
        addChild(jinbi1);
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
        //
        m_unLockButton = new GameSprite(ImagePath("shopItemButonUnclock.png"));
        m_unLockButton->m_touchMeCall = CC_CALLBACK_2(ShopBuildingItemScrollHeadler::unLock, this);
        m_unLockButton->setPosition(itemBgSize.width * 0.29,
                                    -itemBgSize.height * 0.15);
        m_unLockButton->autorelease();
        addChild(m_unLockButton);
        
        Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
        unlockName->setPosition(itemBgSize.width * 0.29,
                                -itemBgSize.height * 0.15);
        addChild(unlockName);
        
        Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",building->getUnlockGold()),
                                                   "fonts/American Typewriter.ttf",
                                                   20);
        unlockLabel->setPosition(itemBgSize.width * 0.29,
                                 -itemBgSize.height * 0.28);
        addChild(unlockLabel);
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
        
        m_upgradeLabel->setString(StringUtils::format("%d",upgradeGold));
        m_levelUpLabel->setString(StringUtils::format("LV.%d",(int)level));
        m_progressBar->updatePercent(level/limitLevel * 100);
        
        int userGold = GameUser::getInstance()->getUserGold();
        if (userGold >= upgradeGold)
        {
            m_upGradeButton->setEnabled(true);
        }else
        {
            m_upGradeButton->setEnabled(false,ImagePath("shopItemButtonDisable.png"));
        }
    }
    
}
void ShopBuildingItemScrollHeadler::upGrade(Touch * touch, Event * event)
{
    GameSprite * spr = (GameSprite *)event->getCurrentTarget();
    if (!spr->isEnable())
    {
        return;
    }
    DefenseBuilding * building = DefenseBuildingManager::getInstance()->getBuildingByIndex(m_index);
    int upgradeGold = building->getStrengthGold();
    int userGold = _G_U->getUserGold();
    if (userGold >= upgradeGold)
    {
        userGold -= upgradeGold;
        _G_U->setUserGold(userGold);
        m_shopScene->updateGoldView();
        building->addStrengthenLevel();
        updateDefenseView();
        GameShowLevelupLayer * showLayer = new GameShowLevelupLayer(building->getModelId());
        showLayer->autorelease();
        m_shopScene->addChild(showLayer);
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
        userGold -= unlockGold;
        _G_U->setUserGold(userGold);
        m_shopScene->updateGoldView();
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