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
    
    
    
    scheduleUpdate();
    _G_V->addChild(this,2);
}
BulletSprite::~BulletSprite()
{
    
}
void BulletSprite::setModel(Bullet *bullet)
{
    m_model = bullet;
    std::string dandao = m_model->getModelId();
    
    initWithFile(ImagePath(dandao));
    
}
void BulletSprite::update(float data)
{
    if (m_model->isMoving()) {
        setPosition(m_model->getPosition());
    }else if (m_model->isArrive())
    {
        m_model->arriveCall();
        _G_V->addBulletTexiao(m_model->getPosition());
    }else if (m_model->isDie())
    {
        m_model->setCanDelete();
        unscheduleUpdate();
        removeFromParentAndCleanup(true);
        return;
    }
}