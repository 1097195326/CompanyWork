//
//  EnemySprite.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemySprite.h"




EnemySprite::EnemySprite(Enemy * model):m_model(model),isHaveArmor(false)
{
    init();
    setAnchorPoint(Vec2(0.5,0));
    
    int w = m_model->getWidth();
    int h = m_model->getHeight();
    
    healthBar = new ProgressBar("xuenei.png","xuewai.png");
    addChild(healthBar,1);
    healthBar->setBarLeft();
    healthBar->setPosition(Vec2(w * 0.5, h * 0.9));
    healthBar->setVisible(false);
    
    
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
void EnemySprite::move()
{}
void EnemySprite::attack()
{}
void EnemySprite::die()
{}
void EnemySprite::hurt()
{}
void EnemySprite::attackCall()
{
    m_model->attackCall();
}
void EnemySprite::dieCall()
{
    m_model->dieingCall();
}
void EnemySprite::hurtCall()
{
    actionStatus = normal;
    m_model->hurtCall();
}