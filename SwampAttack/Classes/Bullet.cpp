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

#define PAI 3.1415f

Bullet::Bullet(BulletParameter bp):m_bp(bp)
{
    m_damage = bp.m_damage;
    if(random(1, 100) < bp.m_critRate * 100)
    {
        m_damage = m_damage * bp.m_critDamageRate;
    }
    
    m_Point= m_StartPoint = m_bp.m_startPoint;
    m_toPoint = m_bp.m_targetPoint;
    
    int accuray = (int)(100 - m_bp.m_accuracy * 100);
    m_toPoint.x += random(-accuray, accuray) ;
    m_toPoint.y += random(-accuray, accuray) ;
    
    m_speed = m_toPoint - m_StartPoint;
    m_speed.normalize();
    
    Vec2 jizhunXian = m_bp.m_target == t_enemy ? Vec2(1, 0) : Vec2(-1, 0);
    m_angle = m_speed.getAngle(jizhunXian) * (180.0f / PAI);
    
    m_speed = m_speed * m_bp.m_bulletSpeed * 0.1;
    
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
    sprite->autorelease();
}
int Bullet::getAttackIndex()
{
    return m_bp.m_underAttackAction;
}
Vec2 Bullet::getPosition()
{
    return m_Point;
}
Rect Bullet::getRect()
{
    return Rect(m_Point.x - m_bp.m_damageArea * 0.5,
                m_Point.y - m_bp.m_damageArea * 0.5,
                m_bp.m_damageArea,
                m_bp.m_damageArea);
}
int Bullet::getDamage()
{
    return m_damage;
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
bool Bullet::isFireEnemy()
{
    return m_bp.m_target == t_enemy;
}
bool Bullet::isFireHouse()
{
    return m_bp.m_target == t_house;
}