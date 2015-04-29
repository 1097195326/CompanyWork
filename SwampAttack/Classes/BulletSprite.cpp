//
//  BulletSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "BulletSprite.h"


BulletSprite::BulletSprite()
{
    init();
    initWithFile(ImagePath("dandao.png"));
    
    
    scheduleUpdate();
}
BulletSprite::~BulletSprite()
{
    
}
void BulletSprite::setModel(Bullet *bullet)
{
    m_model = bullet;
    
}
void BulletSprite::update(float data)
{
    if (m_model->isMoving()) {
        setPosition(m_model->getPosition());
    }else if (m_model->isArrive())
    {
        m_model->arriveCall();
    }else if (m_model->isDie())
    {
        m_model->setCanDelete();
        unscheduleUpdate();
        removeFromParentAndCleanup(true);
        return;
    }
}