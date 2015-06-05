//
//  PropSpriteView.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/4.
//
//

#include "PropSpriteView.h"
#include "GameMapManager.h"
#include "GameFightScene.h"
#include "PropManager.h"

#include "PropSprite_daoju1.h"
#include "PropSprite_daoju2.h"
#include "PropSprite_daoju3.h"
#include "PropSprite_daoju5.h"
#include "PropSprite_daoju6.h"

PropSpriteView::PropSpriteView(Prop * prop):
m_prop(prop),
m_moveJuli(0.0f)
{
    init();
    m_propIcon = NULL;
    
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
    m_listener->onTouchBegan = CC_CALLBACK_2(PropSpriteView::touchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(PropSpriteView::touchMove, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(PropSpriteView::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_blueBg);
    
    _G_V->addChild(this,1);
}
PropSpriteView::~PropSpriteView()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
bool PropSpriteView::touchBegan(Touch *touch, Event *event)
{
    Vec2 p = m_blueBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_blueBg->getContentSize().width ,m_blueBg->getContentSize().height);
    if (r.containsPoint(p)) {
        if (m_prop->getModelId() == "daoju1")
        {
            m_propIcon = new PropSprite_daoju1(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju2")
        {
            m_propIcon = new PropSprite_daoju2(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju3")
        {
            m_propIcon = new PropSprite_daoju3(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju5")
        {
            m_propIcon = new PropSprite_daoju5(m_prop->getId());
        }else if (m_prop->getModelId() == "daoju6")
        {
            m_propIcon = new PropSprite_daoju6(m_prop->getId());
        }else
        {
            m_propIcon = new PropSprite(m_prop->getId());
        }
        m_propIcon->autorelease();
        _G_V->addChild(m_propIcon,5);
         m_propIcon->moveIng(m_blueBg->getPosition());
        return true;
    }
    return false;
}
void PropSpriteView::touchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 touchPoint = touch->getLocation();
    m_propIcon ->moveIng(touchPoint);
}
void PropSpriteView::touchEnd(Touch *touch, Event *event)
{
    m_propIcon->moveEnd();
    m_propIcon = NULL;
}
void PropSpriteView::updateData()
{
    
    
    
}