//
//  EnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemySprite.h"




EnemySprite::EnemySprite(Enemy * model):m_model(model)
{
    init();
    setAnchorPoint(Vec2(0.5,0));
    
    int w = m_model->getWidth();
    int h = m_model->getHeight();
    
    healthBar = new ProgressBar("xuenei.png","xuewai.png");
    healthBar->ignoreAnchorPointForPosition(true);
    addChild(healthBar,1);
    healthBar->setPosition(Vec2(w * 0.5, h * 0.9));
    healthBar->setVisible(false);
    
    
    scheduleUpdate();
}
EnemySprite::~EnemySprite()
{
    std::map<std::string, Action * >::iterator itr;
    for (itr = m_map.begin(); itr != m_map.end(); itr++) {
        Action * ac = itr->second;
        ac->release();
    }
    m_map.clear();
    
    removeAllChildrenWithCleanup(true);
    delete healthBar;
}
void EnemySprite::update(float data)
{
    if (m_model->isDieing())
    {
        die();
    }else if (m_model->isWalk())
    {
        setPosition(m_model->getPosition());
        move();
    }else if (m_model->isAttack())
    {
        attack();
    }else if (m_model->isDied())
    {
        m_model->diedCall();
        unscheduleUpdate();
        removeFromParentAndCleanup(false);
        delete this;
        return;
    }
    if (m_model->isHurt()) {
        healthBar->setVisible(true);
        healthBar->updatePercent(m_model->getHealthPercent());
    }else
    {
        healthBar->setVisible(false);
    }
}
void EnemySprite::move()
{}
void EnemySprite::attack()
{}
void EnemySprite::die()
{}
void EnemySprite::attackCall()
{
    
}
void EnemySprite::dieCall()
{
    m_model->dieingCall();
}