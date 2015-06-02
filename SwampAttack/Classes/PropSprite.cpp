//
//  PropSprite.cpp
//  SwampAttack
//
//  Created by 张洪星 on 15/6/2.
//
//

#include "PropSprite.h"
#include "GameMapManager.h"
#include "GameFightScene.h"
#include "PropManager.h"


PropSprite::PropSprite(Prop * prop):m_prop(prop)
{
    init();
    
    m_iconScale = 0.6;
    int iconIndex = PropManager::getInstance()->getTakeUpPropIndexByName(m_prop->getId());
    m_blueBg = Sprite::create(ImagePath("fight_gun_blueBg.png"));
    Sprite * propIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",m_prop->getModelId().c_str())));
    addChild(m_blueBg);
    addChild(propIcon,5);
    
    m_blueBg->setScale(m_iconScale);
    propIcon->setScale(0.5);
    
    Vec2 iconPoint = _G_M_M->fightScene_PropIcon_Position;
    float iconWidth = m_blueBg->getContentSize().width;
    m_blueBg->setPosition(iconPoint - Vec2(iconWidth * (iconIndex - 1), 0) * m_iconScale);
    propIcon->setPosition(iconPoint - Vec2(iconWidth * (iconIndex - 1), 0) * m_iconScale);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(PropSprite::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(PropSprite::touchMove, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(PropSprite::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_blueBg);
    
    
    updateData();
    _G_V->addChild(this,1);
}
PropSprite::~PropSprite()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
bool PropSprite::touchBegan(Touch *touch, Event *event)
{
    Vec2 p = m_blueBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_blueBg->getContentSize().width ,m_blueBg->getContentSize().height);
    if (r.containsPoint(p)) {
        return true;
    }
    return false;
}
void PropSprite::touchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}
void PropSprite::touchEnd(Touch *touch, Event *event)
{
    log("prop modeld id:%s",m_prop->getModelId().c_str());
//    GunManager::getInstance()->changeGun(m_gun->getId());
}
void PropSprite::updateData()
{
    
    
    
}