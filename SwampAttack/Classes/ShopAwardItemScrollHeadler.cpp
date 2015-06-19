//
//  ShopAwardItemScrollHeadler.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#include "ShopAwardItemScrollHeadler.h"

//#include "GunManager.h"
//#include "PropManager.h"
#include "DefenseBuildingManager.h"
#include "GameUser.h"
#include "GameSprite.h"
#include "SpecialManager.h"


ShopAwardItemScrollHeadler::ShopAwardItemScrollHeadler(int index)
{
    setIndex(index);
    
    
    initAwardView();
}
ShopAwardItemScrollHeadler::~ShopAwardItemScrollHeadler()
{
    //    log("shop item scroll headler remove");
}
void ShopAwardItemScrollHeadler::setGameShopScene(GameShopScene *shopScene)
{
    m_shopScene = shopScene;
}
void ShopAwardItemScrollHeadler::initAwardView()
{
    removeAllChildrenWithCleanup(true);
    
    SpecialObject * specialobject = SpecialManager::getInstance()->getSpecialObjectByIndex(m_index);
    
    GameSprite * itemBg = new GameSprite(ImagePath("shopItemBg1.png"));
    itemBg->autorelease();
    itemBg->m_touchMeCall = CC_CALLBACK_2(ShopAwardItemScrollHeadler::buy, this);
    addChild(itemBg);
    
    Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBg.png"));
    iconBg->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
    addChild(iconBg);
    
    string specialModelId = specialobject->getModelId();
    string specialIconStr = StringUtils::format("%s_icon.png",specialModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(specialIconStr));
    icon->setPosition(iconBg->getContentSize().width * 0.75 - itemBg->getContentSize().width * 0.5, 0);
    addChild(icon);
//    log("name:%s",specialobject->getName().c_str());
    Label * nameLabel = Label::createWithTTF(specialobject->getName(), "fonts/mimi.ttf", 25);
    nameLabel->setPosition(-itemBg->getContentSize().width * 0.08, itemBg->getContentSize().height * 0.18);
    nameLabel->setColor(Color3B(0, 0, 0));
    addChild(nameLabel);
    
    Label * descLabel = Label::createWithTTF(specialobject->getDescription(), "fonts/mimi.ttf", 25);
    descLabel->setPosition(-itemBg->getContentSize().width * 0.15 + descLabel->getContentSize().width * 0.5,
                           -itemBg->getContentSize().height * 0.1);
    descLabel->setColor(Color3B(0, 0, 0));
    addChild(descLabel);
    
    Sprite * moneyBg = Sprite::create(ImagePath("shop_award_moneyBg.png"));
    moneyBg->setPosition(itemBg->getContentSize().width * 0.45,-itemBg->getContentSize().height * 0.15);
    addChild(moneyBg);
    string price = StringUtils::format("$%d",specialobject->getPrice());
    Label * moneyLabel = Label::createWithTTF(price, "fonts/mimi.ttf", 25);
    moneyLabel->setPosition(itemBg->getContentSize().width * 0.45,-itemBg->getContentSize().height * 0.15);
    moneyLabel->setColor(Color3B(0, 0, 0));
    addChild(moneyLabel);
    
//    updateAwardView();
}
void ShopAwardItemScrollHeadler::updateAwardView()
{
    
}
void ShopAwardItemScrollHeadler::buy(cocos2d::Touch *touch, cocos2d::Event *event)
{
    log("buy ...");
    SpecialObject * specialobject = SpecialManager::getInstance()->getSpecialObjectByIndex(m_index);
    
    specialobject->buyEnd();
    m_shopScene->updateGoldView();
    
    
}