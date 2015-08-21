//
//  shopGunIcon.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/27.
//
//

#include "ShopGunIcon.h"
#include "GunManager.h"


ShopGunIcon::ShopGunIcon(int index):m_gun(NULL)
{
    init();
    
    
    if (index == 0)
    {
        m_iconBg = Sprite::create(ImagePath("fight_gun_greenBg.png"));
    }else
    {
        m_iconBg = Sprite::create(ImagePath("fight_gun_blueBg.png"));
    }
    addChild(m_iconBg);
    m_iconBg->setScale(0.65);
    
    m_icon = Sprite::create();
    addChild(m_icon);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->setSwallowTouches(true);
    m_listener->onTouchBegan = CC_CALLBACK_2(ShopGunIcon::touchBegan, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(ShopGunIcon::touchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_iconBg);
    
    setPosition(0, 120 * (1 - index));
}
ShopGunIcon::~ShopGunIcon()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
void ShopGunIcon::reSetIcon(Gun *gun)
{
    if (!gun) {
        return;
    }
    m_icon->removeAllChildrenWithCleanup(true);
    m_gun = gun;
    detachSubject();
    setSubject(m_gun);
    
    
    
    string gunModelId = m_gun->getModelId();
    Sprite * gunIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",gunModelId.c_str())));
    m_icon->addChild(gunIcon);
    gunIcon->setScale(0.6);
    if (!m_gun->isDefaultGun())
    {
        Sprite * noIcon = Sprite::create(ImagePath("shop_No_icon.png"));
        noIcon->setPosition(Vec2(m_iconBg->getContentSize().width * 0.22, m_iconBg->getContentSize().height * 0.25));
        m_icon->addChild(noIcon);
        
        if (m_gun->getWeaponType() != 1)
        {
            m_bullets = Label::createWithTTF("", "fonts/Arial Black.ttf", 17);
            m_icon->addChild(m_bullets);
            m_bullets->setString(StringUtils::format("%d",m_gun->getTotalBulletNum()));
            m_bullets->setPosition(Vec2(m_iconBg->getContentSize().width * 0.15, -m_iconBg->getContentSize().height * 0.2));
            m_bullets->enableOutline(Color4B(0, 0, 0, 255),2);
        }
    }
}
bool ShopGunIcon::isHaveGun()
{
    if (m_gun) {
        return true;
    }
    return false;
}
void ShopGunIcon::updateData()
{
    if (!m_gun->isDefaultGun() && m_gun->getWeaponType() != 1)
    {
        m_bullets->setString(StringUtils::format("%d",m_gun->getTotalBulletNum()));
    }
}
bool ShopGunIcon::touchBegan(Touch *touch, Event *event)
{
    
    Vec2 p = m_iconBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_iconBg->getContentSize().width,m_iconBg->getContentSize().height);
    if (r.containsPoint(p) && this->getParent()->isVisible()) {
        return true;
    }
    return false;
}
void ShopGunIcon::touchEnd(Touch *touch, Event *event)
{
    if (m_gun && !m_gun->isDefaultGun()) {
        m_icon->removeAllChildrenWithCleanup(true);
        detachSubject();
        GunManager::getInstance()->takeDownGun(m_gun->getId());
        m_gun = NULL;
    }
}