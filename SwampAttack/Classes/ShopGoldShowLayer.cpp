//
//  ShopGoldShowLayer.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/23.
//
//

#include "ShopGoldShowLayer.h"
#include "SpecialManager.h"
#include "GameSprite.h"
#include "MobClickCpp.h"

ShopGoldShowLayer::~ShopGoldShowLayer()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
ShopGoldShowLayer::ShopGoldShowLayer(Vec2 position)
{
    init();
    m_point = position;
    
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(ShopGoldShowLayer::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(ShopGoldShowLayer::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    
    layerColor = LayerColor::create(Color4B(0, 0, 0, 0));
    addChild(layerColor);
    layerColor->runAction(FadeTo::create(0.3, 200));
    
    bg = Sprite::create(ImagePath("goldShowBg.png"));
    bg->setPosition(position);
    addChild(bg);
    
    Size bgSize = bg->getContentSize();
    Vec2 itemP = Vec2(bgSize.width * 0.5, bgSize.height * 0.83);
    std::map<int,MoneyObject *>  moneyData = SpecialManager::getInstance()->getMoneyData();
    std::map<int,MoneyObject *>::iterator iter;
    for (iter = moneyData.begin(); iter!= moneyData.end(); ++iter)
    {
        int index = iter->first;
        MoneyObject * object = iter->second;
        
        GameSprite * itemBg = new GameSprite(ImagePath("goldShowItemSpr.png"));
        itemBg->autorelease();
        itemBg->setTag(index);
        itemBg->m_touchMeCall= CC_CALLBACK_2(ShopGoldShowLayer::touchItemEnd, this);
        
        Vec2 p = Vec2(0, itemBg->getContentSize().height * index);
        
        itemBg->setPosition(itemP - p);
        bg->addChild(itemBg);
        
        Size itemSize = itemBg->getContentSize();
        
        std::string iconName = StringUtils::format("%s_icon.png",object->getModelId().c_str());
        Sprite * iconSpr = Sprite::create(ImagePath(iconName));
        iconSpr->setPosition(itemSize.width * 0.1, itemSize.height * 0.5);
        iconSpr->setScale(0.8);
        itemBg->addChild(iconSpr);
        
        Sprite * greenSpr = Sprite::create(ImagePath("goldShowSpr.png"));
        greenSpr->setPosition(itemSize.width * 0.9,itemSize.height * 0.5);
        itemBg->addChild(greenSpr);
        
        SpecialObject * specialObject = SpecialManager::getInstance()->getSpecialObjectBySubId(object->getId(), object->getType());
        Label  * price = Label::createWithTTF(StringUtils::format("$%d",specialObject->getPrice()),
                                              "fonts/Arial Black.ttf",
                                              30);
        price->setPosition(itemSize.width * 0.9, itemSize.height * 0.5);
        itemBg->addChild(price);
        
        Label  * discLabel = Label::createWithTTF(object->getDescription(), FontPath, 30);
        discLabel->setPosition(itemSize.width * 0.5, itemSize.height * 0.5);
        itemBg->addChild(discLabel);
    }
    
    bg->setScale(0.001);
    bg->runAction(Spawn::create(MoveTo::create(0.3,Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                                        m_visibleOrigin.y + m_visibleSize.height * 0.5)),
                                ScaleTo::create(0.3, 1),
                                NULL));
    
}
void ShopGoldShowLayer::setDelegateLayer(UserDelegateLayer * layer)
{
    m_delegateLayer = layer;
}
void ShopGoldShowLayer::touchItemEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    SimpleAudioEngine::getInstance()->playEffect(MusicPath("buyGold.mp3").c_str());
    Sprite * spr = (Sprite *)event->getCurrentTarget();
//    log("touch item %d",spr->getTag());
    MoneyObject * object = SpecialManager::getInstance()->getMoneyObjectByIndex(spr->getTag());
    SpecialObject * specialObject = SpecialManager::getInstance()->getSpecialObjectBySubId(object->getId(), object->getType());
    umeng::MobClickCpp::event(specialObject->getId().c_str());
    
    specialObject->buyEnd();
    m_delegateLayer->updateUserData();
}
bool ShopGoldShowLayer::touchBegan(Touch *touch, Event *event)
{
    return true;
}
void ShopGoldShowLayer::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 point = bg->convertToNodeSpace(touch->getLocation());
    Rect rect = Rect(0, 0, bg->getContentSize().width, bg->getContentSize().height);
    if (rect.containsPoint(point))
    {
        return;
    }
    layerColor->stopAllActions();
    bg->stopAllActions();
    layerColor->runAction(FadeTo::create(0.3, 0));
    bg->runAction(Sequence::create(Spawn::create(MoveTo::create(0.3,m_point),
                                                 ScaleTo::create(0.3, 0.001),
                                                 NULL),
                                   CallFunc::create(CC_CALLBACK_0(ShopGoldShowLayer::actionEndCall, this)),
                                   NULL
                                   ));
}
void ShopGoldShowLayer::actionEndCall()
{
    layerColor->stopAllActions();
    bg->stopAllActions();
    removeFromParentAndCleanup(true);
}