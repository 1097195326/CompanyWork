//
//  AdShowLayer.cpp
//  SwampAttack
//
//  Created by oceantech02 on 16/1/12.
//
//

#include "AdShowLayer.hpp"

AdShowLayer::~AdShowLayer()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
AdShowLayer::AdShowLayer()
{
    init();
    m_point = Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                   m_visibleOrigin.y + m_visibleSize.height * 0.5);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(AdShowLayer::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(AdShowLayer::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    layerColor = LayerColor::create(Color4B(0, 0, 0, 0));
    addChild(layerColor);
    layerColor->runAction(FadeTo::create(0.3, 200));
    
    bg = Sprite::create(ImagePath("ad.png"));
    bg->setPosition(m_point);
    
    
    Size bgSize = bg->getContentSize();
    Vec2 itemP = Vec2(bgSize.width * 0.9, bgSize.height * 0.91);
    
    MenuItem * closeItem = MenuItemImage::create(ImagePath("ad_close.png"),
                                                 ImagePath("ad_close.png"),
                                                 CC_CALLBACK_0(AdShowLayer::closeAd, this));
    Menu * closeButton = Menu::create(closeItem, NULL);
    closeButton->setPosition(itemP);
    bg->addChild(closeButton);
    
    addChild(bg);
    
    bg->setScale(0.001);
    bg->runAction(Spawn::create(MoveTo::create(0.3,Vec2(m_visibleOrigin.x + m_visibleSize.width * 0.5,
                                                        m_visibleOrigin.y + m_visibleSize.height * 0.5)),
                                ScaleTo::create(0.3, 1),
                                NULL));
    
}
bool AdShowLayer::touchBegan(Touch *touch, Event *event)
{
    return true;
}
void AdShowLayer::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}
void AdShowLayer::closeAd()
{
    layerColor->stopAllActions();
    bg->stopAllActions();
    layerColor->runAction(FadeTo::create(0.3, 0));
    bg->runAction(Sequence::create(Spawn::create(MoveTo::create(0.3,m_point),
                                                 ScaleTo::create(0.3, 0.001),
                                                 NULL),
                                   CallFunc::create(CC_CALLBACK_0(AdShowLayer::actionEndCall, this)),
                                   NULL
                                   ));
}
void AdShowLayer::actionEndCall()
{
    layerColor->stopAllActions();
    bg->stopAllActions();
    removeFromParentAndCleanup(true);
}