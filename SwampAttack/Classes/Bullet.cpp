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

#define PAI 3.1415f

Bullet::Bullet(BulletParameter bp, Vec2 fireToPosition)
:m_bp(bp),m_toPoint(fireToPosition)
{
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    
    m_Point= m_StartPoint = gameMap->m_BulletStartPoint;
    
    
    m_speed = fireToPosition - m_StartPoint;
    m_speed.normalize();
    
    m_angle = m_speed.getAngle(Vec2(1, 0)) * (180.0f / PAI);
    
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
        m_Point = m_Point + m_speed * 1;
        if (m_Point.distanceSquared(m_StartPoint) >= m_toPoint.distanceSquared(m_StartPoint)) {
            m_state = _b_arrive;
        }
    }
}
void Bullet::setView()
{
    BulletSprite * sprite = new BulletSprite();
    sprite->setModel(this);
    sprite->setRotation(m_angle);
    _G_D->addChild(sprite,2);
}
Vec2 Bullet::getPosition()
{
    return m_Point;
}
int Bullet::getDamage()
{
    return m_bp.m_damage;
}
void Bullet::arriveCall()
{
    m_state = _b_die;
}
void Bullet::setCanDelete()
{
    m_state = _b_canDelete;
}
bool Bullet::isCanDelete()
{
    return m_state == _b_canDelete;
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