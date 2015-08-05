//
//  WalkEnemy.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#include "WalkEnemy.h"
#include "WalkEnemySprite.h"
#include "CrumpEnemySprite.h"
#include "GameDirector.h"

WalkEnemy::WalkEnemy(Json::Value data):Enemy(data)
{
    
}
void WalkEnemy::gameLoop(float data)
{
    if ((m_status & e_dieing || m_status & e_die))
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
    }else if (m_status & e_walk)
    {
        move();
        if (m_targetPoint.x + m_range >= m_point.x)
        {
            if(!computeIfWander())
            {
                m_status &= e_clear;
                m_status |= e_attack;
            }
        }
    }else if (m_status & e_attack)
    {
//        computeIfWander();
    }else if (m_status & e_wanderF || m_status & e_wanderB)
    {
        wander();
    }
    if (m_isShowHurt)
    {
        hurtDlay += data;
        if (hurtDlay > 3)
        {
            hurtDlay = 0;
            m_isShowHurt = false;
        }
    }
//    Enemy::gameLoop(data);
    std::list<GameBuff *>::iterator iter;

    for (iter = m_buffData.begin(); iter != m_buffData.end();)
    {
//        log("buff size :%d",(int)m_buffData.size());
//        log("state :%d",m_status);
        if ((m_status & e_dieing || m_status & e_die))
        {
            return;
        }
        GameBuff * buff = *iter;
        iter++;
        if (buff->isCanHurt())
        {
            //            log("buff hurt enemy");
            buff->setStateWaiting();
            //            hurt(buff->getDamage() + m_health * buff->getPercentageDamage());
            hurt(buff->getDamage());
        }
    }
}
void WalkEnemy::wander()
{
    if (m_point.distanceSquared(m_perPoint) >= m_toPoint.distanceSquared(m_perPoint))
    {
        m_status &= e_clear;
        m_status |= e_attack;
    }
    else
    {
        if (m_status & e_wanderB)
        {
            m_point += (Vec2(1, 0) * m_speedF);
        }else if (m_status & e_wanderF)
        {
            m_point += (Vec2(-1, 0) * m_speedF);
        }
    }
    
}
void WalkEnemy::move()
{
    m_point = m_point + m_speedV + m_effectSpeedV;
    m_effectSpeedV = Vec2::ZERO;
}
bool WalkEnemy::computeIfWander()
{
    if(m_attackType == 2 && random(1, 100) < 30)
    {
//        log("wander");
        int distance = random(50, 100);
        
        if (m_point.x + distance >= m_targetPoint.x + m_range)
        {
            m_toPoint = m_point + Vec2(-distance, 0);
            m_status &= e_clear;
            m_status |= e_wanderF;
        }else
        {
            m_toPoint = m_point + Vec2(distance, 0);
            m_status &= e_clear;
            m_status |= e_wanderB;
        }
        m_perPoint = m_point;
        return true;
    }
    return false;
}
void WalkEnemy::setView()
{
    if (m_attackType == 3)
    {
        EnemySprite * enemySprite = new CrumpEnemySprite(this);
        enemySprite->autorelease();
    }else
    {
        EnemySprite * enemySprite = new WalkEnemySprite(this);
        enemySprite->autorelease();
    }
    m_status = e_waiting;
}