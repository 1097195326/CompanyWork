//
//  GunSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/20.
//
//

#include "GunSprite.h"
#include "GameMapManager.h"
#include "GameFightScene.h"
#include "GunManager.h"


GunSprite::GunSprite(Gun * gun):m_gun(gun)
{
    init();
    
    if (GunManager::getInstance()->getTakeUpGunNum() > 1)
    {
        m_iconScale = 0.5;
        int iconIndex = GunManager::getInstance()->getTakeUpGunIndexByName(m_gun->getId());
        m_greenBg = Sprite::create(ImagePath("fight_gun_greenBg.png"));
        m_blueBg = Sprite::create(ImagePath("fight_gun_blueBg.png"));
        Sprite * gunIcon = Sprite::create(ImagePath(StringUtils::format("%s_icon.png",m_gun->getModelId().c_str())));
        m_bulletLabel = Label::createWithTTF("", "fonts/Arial Black.ttf", 15);
        m_bulletLabel->enableOutline(Color4B(0, 0, 0, 255),1);
        
        addChild(m_greenBg);
        addChild(m_blueBg);
        addChild(gunIcon,5);
        addChild(m_bulletLabel,6);
        
        m_greenBg->setScale(m_iconScale);
        m_blueBg->setScale(m_iconScale);
        gunIcon->setScale(0.45);
        Vec2 iconPoint = _G_M_M->fightScene_gunIcon_Position;
        float iconWidth = m_greenBg->getContentSize().width;
        m_greenBg->setPosition(iconPoint + Vec2((iconWidth + 10) * (iconIndex - 1), 0) * m_iconScale);
        m_blueBg->setPosition(iconPoint + Vec2((iconWidth + 10) * (iconIndex - 1), 0) * m_iconScale);
        gunIcon->setPosition(iconPoint + Vec2((iconWidth + 10) * (iconIndex - 1), 0) * m_iconScale);
        m_bulletLabel->setPosition(iconPoint + Vec2((iconWidth + 10) * (iconIndex - 1), 0) * m_iconScale + Vec2(20, -20));
        
        m_listener = EventListenerTouchOneByOne::create();
        m_listener->setSwallowTouches(true);
        m_listener->onTouchBegan = CC_CALLBACK_2(GunSprite::touchBegan, this);
        m_listener->onTouchEnded = CC_CALLBACK_2(GunSprite::touchEnd, this);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener, m_greenBg);
    }
    
    
    Vec2 point = _G_M_M->fightScene_Bullet_Position;
    
    int bulletShowType = m_gun->getBulletshowType();
    string gunModelId = m_gun->getModelId();
    
    if (bulletShowType == 2)
    {
        m_bulletProBar = new ProgressBar((gunModelId + "_bulletIcon.png"),
                                         (gunModelId + "_bulletBg.png"));
        m_bulletProBar->autorelease();
        m_bulletProBar->setBarPositon(Vec2(8, 0));
        addChild(m_bulletProBar);
        m_bulletProBar->setBarLeft();
        m_bulletProBar->setPosition(point);
    }else
    {
        int size = m_gun->getMagazieSize();
        m_bullets.reserve(size);
        
        for (int i = 0; i < size; ++i)
        {
            Sprite * b_g = Sprite::create(ImagePath(gunModelId + "_bulletBg.png"));
            Sprite * b_i = Sprite::create(ImagePath(gunModelId + "_bulletIcon.png"));
            
            point.x = point.x - b_g->getContentSize().width * 0.7;
            b_g->setPosition(point);
            b_i->setPosition(point);
            addChild(b_g);
            addChild(b_i);
            m_bullets.push_back(b_i);
            m_bulletsBg.push_back(b_g);
        }
    }
    
    
    updateData();
    _G_V->addChild(this,640);
}
GunSprite::~GunSprite()
{
    if(m_listener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    }
}
bool GunSprite::touchBegan(Touch *touch, Event *event)
{
    Vec2 p = m_greenBg->convertToNodeSpace(touch->getLocation());
    Rect r = Rect(0, 0, m_greenBg->getContentSize().width,m_greenBg->getContentSize().height);
    if (r.containsPoint(p)) {
        return true;
    }
    return false;
}
void GunSprite::touchEnd(Touch *touch, Event *event)
{
    GunManager::getInstance()->changeGun(m_gun->getId());
}
void GunSprite::updateData()
{
    int bulletShowType = m_gun->getBulletshowType();
    int bulletNum = m_gun->getBulletNum();
    int size = m_gun->getMagazieSize();
    
    if (m_gun->isCurrentGun())
    {
        if (bulletShowType == 2) {
            m_bulletProBar->setVisible(true);
            m_bulletProBar->updatePercent((float)bulletNum/(float)size * 100);
        }else
        {
            for (int i = size-1; i >= 0; --i)
            {
                if (i > bulletNum-1)
                {
                    m_bullets[i]->setVisible(false);
                }else
                {
                    m_bullets[i]->setVisible(true);
                }
                m_bulletsBg[i]->setVisible(true);
            }
        }
        if (GunManager::getInstance()->getTakeUpGunNum() > 1)
        {
            m_blueBg->setLocalZOrder(3);
            m_greenBg->setLocalZOrder(4);
            if (!m_gun->isDefaultGun() && m_gun->getWeaponType() != 1)
            {
                string ss= StringUtils::format("%d",m_gun->getTotalBulletNum());
                m_bulletLabel->setString(ss);
            }
        }
    }else
    {
        if (bulletShowType == 2) {
            m_bulletProBar->setVisible(false);
        }else
        {
            for (int i = size-1; i >= 0; --i)
            {
                m_bullets[i]->setVisible(false);
                m_bulletsBg[i]->setVisible(false);
            }
        }
        if (GunManager::getInstance()->getTakeUpGunNum() > 1)
        {
            m_blueBg->setLocalZOrder(4);
            m_greenBg->setLocalZOrder(3);
            if (!m_gun->isDefaultGun() && m_gun->getWeaponType() != 1)
            {
                string ss= StringUtils::format("%d",m_gun->getTotalBulletNum());
                m_bulletLabel->setString(ss);
            }
        }
    }
    
    
}