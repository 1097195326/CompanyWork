//
//  WalkEnemy.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#include "WalkEnemy.h"
#include "WalkEnemySprite.h"
#include "GameDirector.h"

WalkEnemy::WalkEnemy(Json::Value data):Enemy(data)
{
    
    setView();
}
void WalkEnemy::gameLoop(float data)
{
    if (m_status & e_die || m_status & e_dieing)
    {
        return;
    }
    if (m_status == e_waiting)
    {
        dlay += data;
        if (dlay >= tatolDlay)
        {
            dlay = 0;
            m_status &= e_clear;
            m_status |= e_walk;
        }
    }
    if (m_status & e_walk)
    {
        move();
        if (m_targetPoint.x + m_range >= m_point.x)
        {
            m_status &= e_clear;
            m_status |= e_attack;
        }
    }
    if (m_status & e_hurt)
    {
        hurtDlay += data;
        if (hurtDlay > 3)
        {
            m_status &= (~ e_hurt );
            hurtDlay = 0;
        }
    }
}
void WalkEnemy::move()
{
    m_point = m_point + Vec2(-1, 0) * m_speed * 0.1;
}
void WalkEnemy::setView()
{
    EnemySprite * enemySprite = new WalkEnemySprite(m_modelId,this);
    enemySprite->autorelease();
    _G_D->addChild(enemySprite);
}