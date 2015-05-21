//
//  GunSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/20.
//
//

#include "GunBulletSprite.h"
#include "GameMapManager.h"
#include "GameFightScene.h"


GunBulletSprite::GunBulletSprite(Gun * gun):m_gun(gun)
{
    init();
    setSubject(m_gun);
    
    int size = m_gun->getMagazieSize();
    Vec2 point = _G_M_M->fightScene_Bullet_Position;
    m_bullets.reserve(size);
    
    for (int i = 0; i < size; ++i)
    {
        Sprite * b_g = Sprite::create(ImagePath("fight_bullet_bg.png"));
        Sprite * b_i = Sprite::create(ImagePath("fight_bullet_icon.png"));
        
        point.x = point.x - b_g->getContentSize().width;
        b_g->setPosition(point);
        b_i->setPosition(point);
        addChild(b_g);
        addChild(b_i);
        m_bullets.push_back(b_i);
    }
    updateData();
    _G_V->addChild(this,1);
}
void GunBulletSprite::updateData()
{
    int bulletNum = m_gun->getBulletNum();
    int size = m_gun->getMagazieSize();
    for (int i = size-1; i >= 0; --i)
    {
        if (i > bulletNum-1)
        {
            m_bullets[i]->setVisible(false);
        }else
        {
            m_bullets[i]->setVisible(true);
        }
    }
}