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
    canMoveBack = false;
    randomPoint();
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
    if (m_status & e_walk || isHurt())
    {
        move();
    }
    if (dlayToAttack >= 3) {
        if (m_targetPoint.x + m_range >= m_point.x)
        {
            dlayToAttack = 0;
            m_status |= e_attack;
        }
    }else
    {
        dlayToAttack += data;
    }
    if (!canMoveBack && m_point.x <= m_visibleOrigin.x + m_visibleSize.width * 0.3) {
        canMoveBack = true;
    }
    if (m_isShowHurt)
    {
        hurtDlay += data;
        if (hurtDlay > 3)
        {
            m_isShowHurt = false;
            hurtDlay = 0;
        }
    }
}

void FlyEnemy::move()
{
    if (m_speedVec.x > 0 && m_point.x >= m_nextPoint.x)
    {
        randomPoint();
    }else if (m_speedVec.x < 0 && m_point.x <= m_nextPoint.x)
    {
        randomPoint();
    }
    m_point = m_point + m_speedVec;
}
void FlyEnemy::setView()
{
    EnemySprite * enemySprite = new FlyEnemySprite(this);
    enemySprite->autorelease();
    m_status = e_waiting;
}
void FlyEnemy::randomPoint()
{
    setPointState();
    
    Vec2 backForce, frontForce, buttomForce, upForce, normalForce;
    if (m_pointState & p_back)
    {
        backForce = Vec2(-(random(0, 100)+100), 0);
    }
    if (m_pointState & p_front)
    {
        frontForce = Vec2(random(0, 100)+100, 0);
    }
    if (m_pointState & p_bottom)
    {
        buttomForce = Vec2(0, random(0, 100)+100);
    }
    if (m_pointState & p_up)
    {
        upForce = Vec2(0,-(random(0, 100)+100));
    }
    if (canMoveBack)
    {
        log("can move back");
         normalForce =Vec2(random(-150, 100), random(-150, 150));
    }else
    {
         normalForce =Vec2(random(-150, 0), random(-150, 150));
    }
   
    m_nextPoint = m_point + normalForce + frontForce + backForce + buttomForce + upForce;
    
    if (m_nextPoint.y > m_visibleOrigin.y + m_visibleSize.height)
    {
        m_nextPoint.y = m_visibleOrigin.y + m_visibleSize.height;
    }
//    log("move x ::%f",m_nextPoint.x - m_point.x);
//    log("move y ::%f",m_nextPoint.y - m_point.y);
    m_speedVec = m_nextPoint - m_point;
    m_speedVec.normalize();
    m_speedVec = m_speedVec * m_speedF;
    
}
void FlyEnemy::setPointState()
{
    float backLine = m_visibleOrigin.x + m_visibleSize.width * 0.8;
    float frontLine = m_visibleOrigin.x + m_visibleSize.width * 0.4;
    float bottomLine = m_visibleOrigin.y + m_visibleSize.height * 0.3;
    float upLine = m_visibleOrigin.y + m_visibleSize.height * 0.7;
    
    if (m_point.x >= backLine)
    {
        m_pointState |= p_back;
    }else
    {
        m_pointState &= (~p_back);
    }
    if (m_point.x <= frontLine)
    {
        m_pointState |= p_front;
    }else
    {
        m_pointState &= (~p_front);
    }
    if (m_point.y <= bottomLine)
    {
        m_pointState |= p_bottom;
    }else
    {
        m_pointState &= (~p_bottom);
    }
    if (m_point.y >= upLine)
    {
        m_pointState |= p_up;
    }else
    {
        m_pointState &= (~p_up);
    }
}
