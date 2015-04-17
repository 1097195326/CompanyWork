//
//  Bullet.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "Bullet.h"
#include "GameMapManager.h"
#include "BulletSprite.h"
#include "GameDirector.h"


Bullet::Bullet(BulletParameter bp, Vec2 fireToPosition)
:m_bp(bp),m_toPoint(fireToPosition)
{
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    
    m_Point= m_StartPoint = gameMap->m_BulletStartPoint;
    
    m_angle = Vec2::angle(fireToPosition, m_StartPoint);
    log("angle : %f",m_angle);
    
    m_speed = fireToPosition - m_StartPoint;
    m_speed.normalize();
    m_speed = m_speed * m_bp.m_bulletSpeed;
    
    m_state = _b_moving;
    
    setView();
}
Bullet::~Bullet()
{
    
}
void Bullet::gameLoop(float data)
{
    if (m_state == _b_moving)
    {
        m_Point = m_Point + m_speed * 0.1;
        if (m_Point.distanceSquared(m_StartPoint) > m_toPoint.distanceSquared(m_StartPoint)) {
            m_state = _b_arrive;
        }
    }
}
void Bullet::setView()
{
    BulletSprite * sprite = new BulletSprite();
    sprite->setModel(this);
    _G_D->addChild(sprite,2);
//    sprite->setRotation(m_angle);
}
Vec2 Bullet::getPosition()
{
    return m_Point;
}
void Bullet::arriveCall()
{
    m_state = _b_die;
}
bool Bullet::isMoving()
{
    return m_state == _b_moving;
}
bool Bullet::isArrive()
{
    return m_state == _b_arrive;
}
bool Bullet::isDie()
{
    return m_state == _b_die;
}