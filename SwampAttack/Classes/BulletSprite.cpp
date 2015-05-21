//
//  BulletSprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "BulletSprite.h"
#include "GameFightScene.h"


BulletSprite::BulletSprite()
{
    init();
    initWithFile(ImagePath("dandao.png"));
    
    
    scheduleUpdate();
    _G_V->addChild(this,2);
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