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
    if (!canMoveBack && m_point.x <= m_targetPoint.x + m_range) {
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
    if (m_point.distanceSquared(m_perPoint) >= m_nextPoint.distanceSquared(m_perPoint))
    {
        randomPoint();
    }
    
    if (m_point.y >= m_visibleOrigin.y + m_visibleSize.height - 80 ||
        m_point.y <= m_visibleOrigin.y + 80) {
        randomPoint();
//        return;
    }
    m_point = m_point + m_speedVec;
}
void FlyEnemy::effectAction(cocos2d::Vec2 point)
{
    if (m_point.x >= m_visibleOrigin.x + m_visibleSize.width - 60)
    {
        return;
    }
    Vec2 force = (m_point - point);
//    log("effect force %f:%f",force.x,force.y);
    force.normalize();
    m_speedVec += (force * 3);
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
        backForce = Vec2(-(random(0, 100)+50), 0);
    }
    if (m_pointState & p_front)
    {
        frontForce = Vec2(random(0, 100)+50, 0);
    }
    if (m_pointState & p_bottom)
    {
        buttomForce = Vec2(0, random(0, 100)+50);
    }
    if (m_pointState & p_up)
    {
        upForce = Vec2(0,-(random(0, 100)+50));
    }
    if (canMoveBack)
    {
         normalForce =Vec2(random(-100, 50), random(-50, 50));
    }else
    {
         normalForce =Vec2(random(-100, 0), random(-50, 50));
    }
   
    m_nextPoint = m_point + normalForce + frontForce + backForce + buttomForce + upForce;
    
    if (m_nextPoint.y > m_visibleOrigin.y + m_visibleSize.height)
    {
        m_nextPoint.y = m_visibleOrigin.y + m_visibleSize.height;
    }
    m_perPoint = m_point;
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
    float upLine = m_visibleOrigin.y + m_visibleSize.height * 0.68;
//    log("x:y = %f:%f",m_point.x,m_point.y);
    if (m_point.x >= backLine)
    {
//        log("back");
        m_pointState |= p_back;
    }else
    {
//        log("no back");
        m_pointState &= (~p_back);
    }
    if (m_point.x <= frontLine)
    {
//        log("font");
        m_pointState |= p_front;
    }else
    {
//        log("no font");
        m_pointState &= (~p_front);
    }
    if (m_point.y <= bottomLine)
    {
//        log("buttom");
        m_pointState |= p_bottom;
    }else
    {
//        log("no buttom");
        m_pointState &= (~p_bottom);
    }
    if (m_point.y >= upLine)
    {
//        log("up");
        m_pointState |= p_up;
    }else
    {
//        log("no up");
        m_pointState &= (~p_up);
    }
}
