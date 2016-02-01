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
#include "MobClickCpp.h"

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
    
    GameSprite * itemBg = new GameSprite(ImagePath("shopItemBg4.png"));
    itemBg->autorelease();
    itemBg->m_touchMeCall = CC_CALLBACK_2(ShopAwardItemScrollHeadler::buy, this);
    addChild(itemBg);
    
    Size itemBgSize = itemBg->getContentSize();
    
    Sprite * iconBg = Sprite::create(ImagePath("shopItemIconBlueBg.png"));
    iconBg->setPosition(itemBgSize.width * 0.15,
                        itemBgSize.height * 0.5);
    itemBg->addChild(iconBg);
    
    string specialModelId = specialobject->getModelId();
    string specialIconStr = StringUtils::format("%s_icon.png",specialModelId.c_str());
    Sprite * icon = Sprite::create(ImagePath(specialIconStr));
    icon->setPosition(itemBgSize.width * 0.15,
                      itemBgSize.height * 0.5);
    itemBg->addChild(icon);
//    log("name:%s",specialobject->getName().c_str());
    Label * nameLabel = Label::createWithTTF(specialobject->getName(), FontPath, 35);
    nameLabel->setPosition(itemBgSize.width * 0.46,
                           itemBgSize.height * 0.7);
//    nameLabel->setColor(Color3B(0, 0, 0));
    itemBg->addChild(nameLabel);
    
    Label * descLabel = Label::createWithTTF(specialobject->getDescription(), FontPath, 30);
    descLabel->setPosition(itemBgSize.width * 0.35
                           + descLabel->getContentSize().width * 0.5,
                           itemBgSize.height * 0.4);
//    descLabel->setColor(Color3B(0, 0, 0));
    itemBg->addChild(descLabel);
    
    Sprite * moneyBg = Sprite::create(ImagePath("shop_award_moneyBg.png"));
    moneyBg->setPosition(itemBgSize.width * 1,
                         itemBgSize.height * 0.4);
    itemBg->addChild(moneyBg);
    string price = StringUtils::format("$%d",specialobject->getPrice());
    if (specialobject->getType() == 1) {
        price = StringUtils::format("$%d",specialobject->getPrice());
    }else
    {
        price = StringUtils::format("%d",specialobject->getPrice());
        Sprite * jinbi2 = Sprite::create(ImagePath("jinbi_icon.png"));
        jinbi2->setPosition(itemBgSize.width * 1.05,
                            itemBgSize.height * 0.4);
        jinbi2->setScale(0.75);
        itemBg->addChild(jinbi2);
    }
    Label * moneyLabel = Label::createWithTTF(price, "fonts/Arial Black.ttf", 25);
    moneyLabel->setPosition(itemBgSize.width * 0.95,
                            itemBgSize.height * 0.4);
    moneyLabel->enableOutline(Color4B(0, 0, 0, 255),3);
    moneyLabel->setAdditionalKerning(-3);
    itemBg->addChild(moneyLabel);
    
//    updateAwardView();
}
void ShopAwardItemScrollHeadler::updateAwardView()
{
    
}
void ShopAwardItemScrollHeadler::buy(cocos2d::Touch *touch, cocos2d::Event *event)
{
    log("buy ...");
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buyGold.mp3").c_str());
    SpecialObject * specialobject = SpecialManager::getInstance()->getSpecialObjectByIndex(m_index);
    umeng::MobClickCpp::event(specialobject->getId().c_str());
    
    specialobject->buyEnd();
//    m_shopScene->updateUserData();
    
    
}