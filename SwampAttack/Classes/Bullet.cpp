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
#include "EnemyManager.h"
#include "House.h"
#include "BulletManager.h"

#define PAI 3.1415f

Bullet::Bullet(BulletParameter bp):
m_bp(bp),
m_effectDistance(120),
m_enemy(NULL)
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
    
    m_speed = m_speed * m_bp.m_bulletSpeed * 1;
    
    m_state = _b_moving;
    
    m_bulletModel = BulletManager::getInstance()->getBulletModelById(m_bp.m_modelId);
    
//    setView();
}
Bullet::~Bullet()
{
    
}
void Bullet::move()
{
    m_Point = m_Point + m_speed * 0.1;
}
void Bullet::gameLoop(float data)
{
    if (m_state == _b_moving)
    {
        
        move();
        if (m_Point.distanceSquared(m_StartPoint) >= m_toPoint.distanceSquared(m_StartPoint))
        {
            m_state = _b_arrive;
        }
    }
    if (m_state == _b_arrive) {
        if (isFireHouse())
        {
            House::getInstance()->hurt(m_damage);
            return;
        }
        EnemyGroup * enemyGroup = EnemyManager::getInstance()->getCurrectGroup();
        if (!enemyGroup) {
            return;
        }
        std::list<Enemy*> enemyData =enemyGroup->getShowEnemyData();
        if (!enemyData.empty())
        {
            std::list<Enemy*>::iterator e_iter;
            for (e_iter = enemyData.begin() ; e_iter != enemyData.end(); ++e_iter)
            {
                Enemy * enemy = *e_iter;
                Rect b_rect = getRect();
                if (isFireEnemy() &&
                    !enemy->isDied() &&
                    enemy->isContainsPoint(b_rect))
                {
                    if (m_bp.m_damageArea > 0)
                    {
                        enemy->hurt(m_damage,m_bp.m_underAttackAction);
                    }else
                    {
                        if (m_enemy && m_enemy->getPosition().y > enemy->getPosition().y)
                        {
                            m_enemy = enemy;
                        }else
                        {
                            m_enemy = enemy;
                        }
                    }
                }
                if (enemy->getActionType() == 2 &&
                    !enemy->isDied() &&
                    m_Point.distance(enemy->getEnemyCenterPoint()) <= m_effectDistance
                    )
                {
                    enemy->effectAction(m_Point);
                }
            }
            if (m_enemy)
            {
//                if (m_enemy->getActionType() == 2)
//                {
//                    return;
//                    m_enemy = NULL;
//                }
                m_enemy->hurt(m_damage,m_bp.m_underAttackAction);
                m_enemy = NULL;
            }
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
int Bullet::getFlyActionType()
{
    return m_bulletModel->getEffect();
}
std::string Bullet::getModelId()
{
    return m_bulletModel->getModelId();
}
Vec2 Bullet::getStartPosition()
{
    return m_StartPoint;
}
Vec2 Bullet::getToPosition()
{
    return m_toPoint;
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
bool Bullet::isHaveExplode()
{
    return m_bulletModel->isHaveExplode();
}
BulletInfoData Bullet::getDandaoInfo()
{
    BulletInfoData data;
    string modelId = m_bulletModel->getModelId();
    
    if ("BulletModelId1" == modelId)
    {
        data.name = "BulletModelId1";
        data.frames = 1;
    }else if ("BulletModelId2" == modelId)
    {
        data.name = "enemy_bullet";
        data.frames = 3;
    }else if ("BulletModelId3" == modelId)
    {
        data.name = "bat_bullet";
        data.frames = 4;
    }else if ("BulletModelId4" == modelId)
    {
        data.name = "BulletModelId4";
        data.frames = 1;
    }else if ("BulletModelId5" == modelId)
    {
        data.name = "BulletModelId5";
        data.frames = 3;
    }else if ("BulletModelId6" == modelId)
    {
        data.name = "qiang10_bullet";
        data.frames = 3;
    }else if ("BulletModelId7" == modelId)
    {
        data.name = "bullet_qiang11";
        data.frames = 4;
    }else if ("BulletModelId8" == modelId)
    {
        data.name = "bullet_qiang12";
        data.frames = 6;
    }else
    {
        data.name = "";
        data.frames = 0;
    }
    return data;
}
BulletInfoData Bullet::getBaozhaTexiaoInfo()
{
    BulletInfoData data;
    string ex = m_bulletModel->getExplode();
    
    if ("blast1" == ex)
    {
        data.name = "bullet_hit";
        data.frames = 6;
    }else if ("blast2" == ex)
    {
        data.name = "explosion";
        data.frames = 14;
    }
    
    return data;
}