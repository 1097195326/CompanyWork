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
        
        GameSprite * iconBg = new GameSprite(ImagePath("shopItemIconBg.png"));
        iconBg->autorelease();
        iconBg->m_touchMeCall = CC_CALLBACK_2(ShopBuildingItemScrollHeadler::showDiscView, this);
        
//        Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
        iconBg->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
        addChild(iconBg);
        
        string buildingModelId = building->getModelId();
        string buildingIconStr = StringUtils::format("%s_icon.png",buildingModelId.c_str());
        string buildingNameStr = StringUtils::format("%s_name.png",buildingModelId.c_str());
        Sprite * icon = Sprite::create(ImagePath(buildingIconStr));
        icon->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
        addChild(icon);
        
        Sprite * iconName = Sprite::create(ImagePath(buildingNameStr));
        iconName->setPosition(-itemBg->getContentSize().width * 0.25 + iconName->getContentSize().width * 1, itemBg->getContentSize().height * 0.18);
        addChild(iconName);
        
        m_upGradeButton = MenuItemImage::create(ImagePath("shopItemButtonNormal.png"),
                                                ImagePath("shopItemButtonNormal.png"),
                                                CC_CALLBACK_1(ShopBuildingItemScrollHeadler::upGrade, this));
        
        m_upGradeButton->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        Menu * buttonMenu = Menu::create(m_upGradeButton, NULL);
        buttonMenu->setPosition(Point::ZERO);
        addChild(buttonMenu);
        
        Sprite * upgradeLabel = Sprite::create(ImagePath("shopItemLabel1.png"));
        upgradeLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.1);
        addChild(upgradeLabel);
        
        m_progressBar = new ProgressBar("shopItemTiao1.png","shopItemTiao2.png");
        m_progressBar->setBarRight();
        m_progressBar->setPosition(itemBg->getContentSize().width * 0.29, itemBg->getContentSize().height * 0.18);
        addChild(m_progressBar);
        m_upgradeLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 20);
        m_upgradeLabel->setPosition(itemBg->getContentSize().width * 0.33, -itemBg->getContentSize().height * 0.25);
        addChild(m_upgradeLabel);
        Sprite * jinbi1 = Sprite::create(ImagePath("jinbi_icon.png"));
        jinbi1->setPosition(itemBg->getContentSize().width * 0.4, -itemBg->getContentSize().height * 0.23);
        addChild(jinbi1);
    }else
    {
        Sprite * itemBg = Sprite::create(ImagePath("shopItemBg2.png"));
        addChild(itemBg);
        //
        string buildingModelId = building->getModelId();
        string buildingIconStr = StringUtils::format("%s_grayicon.png",buildingModelId.c_str());
        string buildingNameStr = StringUtils::format("%s_name.png",buildingModelId.c_str());
        Sprite * icon = Sprite::create(ImagePath(buildingIconStr));
        icon->setPosition(icon->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
        addChild(icon);
        Sprite * lockIcon = Sprite::create(ImagePath("shopItemLockIcon.png"));
        lockIcon->setPosition(icon->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
        addChild(lockIcon);
        
        Sprite * iconName = Sprite::create(ImagePath(buildingNameStr));
        iconName->setPosition(-itemBg->getContentSize().width * 0.25 + iconName->getContentSize().width * 1, itemBg->getContentSize().height * 0.18);
        addChild(iconName);
        //
        m_unLockButton = MenuItemImage::create(ImagePath("shopItemButonUnclock.png"),
                                               ImagePath("shopItemButonUnclock.png"),
                                               CC_CALLBACK_1(ShopBuildingItemScrollHeadler::unLock, this));
        
        m_unLockButton->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        Menu * buttonMenu = Menu::create(m_unLockButton, NULL);
        buttonMenu->setPosition(Point::ZERO);
        addChild(buttonMenu);
        Sprite * unlockName = Sprite::create(ImagePath("shopItemUnlockName.png"));
        unlockName->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.15);
        addChild(unlockName);
        
        Label * unlockLabel = Label::createWithTTF(StringUtils::format("%d",building->getUnlockGold()),
                                                   "fonts/American Typewriter.ttf",
                                                   20);
        unlockLabel->setPosition(itemBg->getContentSize().width * 0.29, -itemBg->getContentSize().height * 0.28);
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
        m_progressBar->updatePercent(level/limitLevel * 100);
        
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
    }
    
}
void ShopBuildingItemScrollHeadler::upGrade(Ref * pSender)
{
    
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
void ShopBuildingItemScrollHeadler::unLock(Ref * pSender)
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
void ShopBuildingItemScrollHeadler::buy(Ref * pSender)
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