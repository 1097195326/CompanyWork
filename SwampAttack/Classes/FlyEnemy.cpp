//
//  FlyEnemy.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#include "FlyEnemy.h"
#include "FlyEnemySprite.h"
#include "GameDirector.h"

FlyEnemy::FlyEnemy(Json::Value data):Enemy(data)
{
    
}
void FlyEnemy::gameLoop(float data)
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
void FlyEnemy::move()
{
    m_point = m_point + Vec2(-1,0) * m_speed * 0.1;
}
void FlyEnemy::setView()
{
    EnemySprite * enemySprite = new FlyEnemySprite(m_modelId,this);
    _G_D->addChild(enemySprite);
}
