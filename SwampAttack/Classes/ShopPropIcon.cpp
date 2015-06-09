//
//  ShopPropIcon.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/28.
//
//

#include "ShopPropIcon.h"

#include "PropManager.h"


ShopPropIcon::ShopPropIcon(int index)
{
    init();
    
    m_iconBg = Sprite::create(ImagePath("fight_gun_blueBg.png"));
    
    addChild(m_iconBg);
    
    m_icon = Sprite::create();
    addChild(m_icon);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(ShopPropIcon::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(ShopPropIcon::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_iconBg);
    
    setPosition(0, 120 * (1 - index));
}
ShopPropIcon::~ShopPropIcon()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
void ShopPropIcon::reSetIcon(Prop * prop)
{
    if (!prop) {
        return;
    }
    m_icon->removeAllChildrenWithCleanup(true);
    m_prop = prop;
    detachSubject();
    setSubject(m_prop);
    string gunModelId = m_prop->getModelId();
    
    Sprite * gunIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",gunModelId.c_str())));
    m_icon->addChild(gunIcon);
    m_num = Label::createWithTTF("", "fonts/Arial Black.ttf", 18);
    m_icon->addChild(m_num);
    m_num->setString(StringUtils::format("%d",m_prop->getNum()));
    m_num->setPosition(Vec2(m_iconBg->getContentSize().width * 0.2, -m_iconBg->getContentSize().height * 0.3));
    m_num->setColor(Color3B(0, 0, 0));
}
void ShopPropIcon::updateData()
{
    m_num->setString(StringUtils::format("%d",m_prop->getNum()));
    
}
bool ShopPropIcon::touchBegan(Touch *touch, Event *event)
{
    Vec2 p = m_iconBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_iconBg->getContentSize().width,m_iconBg->getContentSize().height);
    if (r.containsPoint(p) && this->getParent()->isVisible()) {
        return true;
    }
    return false;
}
void ShopPropIcon::touchEnd(Touch *touch, Event *event)
{
    if (m_prop) {
        m_icon->removeAllChildrenWithCleanup(true);
        detachSubject();
        PropManager::getInstance()->takeDownProp(m_prop->getId());
        m_prop = NULL;
    }
}
