//
//  GameSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/10.
//
//

#include "GameSprite.h"

GameSprite::GameSprite(std::string name):
m_isTouchMe(false)
{
//    init();
    initWithFile(name);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(false);
    m_listener->onTouchBegan = CC_CALLBACK_2(GameSprite::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(GameSprite::touchMoved, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(GameSprite::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    
}
GameSprite::~GameSprite()
{
    if (m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
void GameSprite::setCanSwallowTouches(bool can)
{
    m_listener->setSwallowTouches(can);
}

bool GameSprite::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 point = this->convertToNodeSpace(touch->getLocation());
    Rect rect = Rect(0, 0, getContentSize().width, getContentSize().height);
    if (rect.containsPoint(point))
    {
//        log("game sprite touch");
        m_isTouchMe = true;
        return true;
    }
    return false;
}
void GameSprite::touchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    m_isTouchMe = false;
}
void GameSprite::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (m_isTouchMe)
    {
        m_touchMeCall(touch,event);
    }
}