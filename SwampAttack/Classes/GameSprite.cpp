//
//  GameSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/10.
//
//

#include "GameSprite.h"

GameSprite::GameSprite(std::string name):
m_name(name),
m_isTouchMe(false),
m_isEnable(true),
m_isCanScale(true),
m_isCanTouch(true)
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
void GameSprite::setCanScale(bool canScale)
{
    m_isCanScale = canScale;
}
void GameSprite::setEnabled(bool enable,std::string name)
{
    m_isEnable = enable;
    if (name.size() > 0)
    {
        if (m_isEnable)
        {
            setTexture(m_name);
        }else
        {
            setTexture(name);
        }
    }
}
bool GameSprite::isEnable()
{
    return m_isEnable;
}
void GameSprite::setCanTouch(bool can)
{
    m_isCanTouch = can;
}
bool GameSprite::isCanTouch()
{
    return m_isCanTouch;
}
bool GameSprite::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (!m_isCanTouch)
    {
        return false;
    }
    Vec2 point = this->convertToNodeSpace(touch->getLocation());
    Rect rect = Rect(0, 0, getContentSize().width, getContentSize().height);
    if (rect.containsPoint(point))
    {
//        log("game sprite touch began");
        if (m_isCanScale)
        {
            runAction(ScaleTo::create(0.1, 0.9));
        }
        m_isTouchMe = true;
        m_moveLength = Vec2::ZERO;
        return true;
    }
    return false;
}
void GameSprite::touchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    log("game sprite move");
    m_isTouchMe = false;
    m_moveLength += touch->getLocation() - touch->getPreviousLocation();
    
}
void GameSprite::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    log("game sprite touch end");
    if (m_isCanScale)
    {
        runAction(ScaleTo::create(0.1, 1));
    }
//    log("game sprite move length:%f",m_moveLength.length());
    
//    if (m_isTouchMe)
//    {
//        m_touchMeCall(touch,event);
//    }
    if(m_moveLength.length() < 3)
    {
    	m_touchMeCall(touch,event);
    }
    m_moveLength = Vec2::ZERO;
}
