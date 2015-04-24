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
    dlayToAttack = 0;
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
    }
    if (dlayToAttack >= 2) {
        dlayToAttack = 0;
        if (m_targetPoint.x + m_range >= m_point.x)
        {
            m_status |= e_attack;
        }
    }else
    {
        dlayToAttack += data;
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
    if (m_point == m_nextPoint) {
        randomPoint();
    }
    m_point = m_point + m_speedVec * 0.1;
}
void FlyEnemy::setView()
{
    EnemySprite * enemySprite = new FlyEnemySprite(m_modelId,this);
    _G_D->addChild(enemySprite);
}
void FlyEnemy::randomPoint()
{
    setPointState();
    
    Vec2 backForce, frontForce, buttomForce, upForce, normalForce;
    if (m_pointState & p_back)
    {
        backForce = Vec2(-(random(0, 50)+30), 0);
    }
    if (m_pointState & p_front)
    {
        frontForce = Vec2(random(0, 50)+30, 0);
    }
    if (m_pointState & p_bottom)
    {
        buttomForce = Vec2(0, random(0, 50)+30);
    }
    if (m_pointState & p_up)
    {
        buttomForce = Vec2(0,-(random(0, 50)+30));
    }
    normalForce =Vec2(random(-50, 50), random(-50, 50));
    m_nextPoint = normalForce + frontForce + backForce + buttomForce + upForce;
    
    m_speedVec = m_nextPoint - m_point;
    m_speedVec.normalize();
    m_speedVec = m_speedVec * m_speed;
    
}
void FlyEnemy::setPointState()
{
    float backLine = visibleOrigin.x + visibleSize.width * 0.9;
    float frontLine = visibleOrigin.x + visibleSize.width * 0.2;
    float buttomLine = visibleOrigin.y + visibleSize.height * 0.3;
    float upLine = visibleOrigin.y + visibleSize.height * 0.8;
    
    if (m_point.x >= backLine)
    {
        m_status |= p_back;
    }else
    {
        m_status &= (~p_back);
    }
    if (m_point.x <= frontLine)
    {
        m_status |= p_front;
    }else
    {
        m_status &= (~p_front);
    }
    if (m_point.y <= buttomLine)
    {
        m_status |= p_bottom;
    }else
    {
        m_status &= (~p_bottom);
    }
    if (m_point.y >= upLine)
    {
        m_status |= p_up;
    }else
    {
        m_status &= (~p_up);
    }
}
