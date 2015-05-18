//
//  Enemy.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "Enemy.h"
#include "GameMapManager.h"
#include "EnemyInfo.h"
#include "House.h"
#include "BulletManager.h"

Enemy::Enemy(Json::Value data):m_data(data),m_isShowHurt(false)
{
    
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    m_point = gameMap->m_startPoint + Vec2(random(10, 200), random(1, 10));
    m_targetPoint = gameMap->m_targetPoint;
    ///--- set status ---
    m_status = e_waiting;
    ///------set data-------
    m_id = m_data["Id"].asString();
    m_monsterName = m_data["MonsterName"].asString();
    m_modelId = m_data["ModelId"].asString();
    m_width = EnemyInfo::getInstance()->getInfoByName(m_modelId).width;
    m_height = EnemyInfo::getInstance()->getInfoByName(m_modelId).height;
    m_actionType = atoi(m_data["ActionType"].asString().c_str());
    m_bulletModelId = m_data["BulletModelId"].asString();
    m_attackType = atoi(m_data["AttackType"].asString().c_str());
    m_bulletSpeed = atof(m_data["BulletSpeed"].asString().c_str());
    m_level = atoi(m_data["Level"].asString().c_str());
    m_totalHealth = m_health = atoi(m_data["Hp"].asString().c_str());
    m_speed = atof(m_data["Speed"].asString().c_str());
    m_damage = atof(m_data["Damage"].asString().c_str());
    
    float as = atof(m_data["AttackSpeed"].asString().c_str()) ;
    float af = EnemyInfo::getInstance()->getInfoByName(m_modelId).attackFrames;
    m_attackSpeed = 1.0f / as / af ;
    m_range = atof(m_data["Range"].asString().c_str());
    m_gold = atoi(m_data["Gold"].asString().c_str());
    m_drop = m_data["Drop"].asString();
    
    dlay = 0;
    tatolDlay = random(0, 130) / 100.0f;
    hurtDlay = 0;
}
Enemy::~Enemy()
{
    
}
void Enemy::gameLoop(float data){}
void Enemy::move(){}
void Enemy::setView(){}
bool Enemy::isContainsPoint(cocos2d::Rect rect)
{
    m_rect = Rect(m_point.x - m_width * 0.5, m_point.y, m_width, m_height);
    return m_rect.intersectsRect(rect);
}
void Enemy::hurt(int damage,int index)
{
    m_health = m_health - damage;
    if (m_health <= 0)
    {
        m_status &= e_clear;
        m_status |= e_dieing;
    }else
    {
        hurtDlay = 0;
        m_isShowHurt = true;
        m_status &= e_clear;
        switch (index) {
            case 1:
                m_status |= e_hurt1;
                break;
            case 2:
                m_status |= e_hurt2;
                break;
            case 3:
                m_status |= e_hurt3;
                break;
        }
    }
    log("enemy health :%f",m_health);
}
//--- view 接口
bool Enemy::isShowHurt()
{
    return m_isShowHurt;
}
bool Enemy::isDieing()
{
    return m_status & e_dieing;
}
bool Enemy::isWalk()
{
    return m_status & e_walk;
}
bool Enemy::isHurt()
{
    return m_status & e_hurt1 || m_status & e_hurt2 || m_status & e_hurt3;
}
int Enemy::getHurtIndex()
{
    switch (m_status) {
        case e_hurt1:
            return 1;
            break;
        case e_hurt2:
            return 2;
            break;
        case e_hurt3:
            return 3;
            break;
        default:
            return 0;
            break;
    }
}
bool Enemy::isAttack()
{
    return m_status & e_attack;
}
bool Enemy::isDied()
{
    return m_status & e_die;
}
bool Enemy::isCanDelete()
{
    return m_status & e_canDel;
}
Vec2 Enemy::getPosition()
{
    return m_point;
}
Vec2 Enemy::getTargetPosition()
{
    return m_targetPoint;
}
void Enemy::dieingCall()
{
    m_status &= e_clear;
    m_status |= e_die;
}
void Enemy::diedCall()
{
//    m_status &= e_clear;
    m_status |= e_canDel;
}
void Enemy::hurtCall()
{
    m_status &= e_clear;
    m_status |= e_walk;
}
void Enemy::attackCall()
{
    switch (m_attackType) {
        case 1:     // 陆地 近程
            House::getInstance()->hurt(m_damage);
            break;
        case 2:     // 陆地 远程
        {
            BulletParameter bp(m_damage,
                               0,
                               1,
                               0,
                               0,
                               1,
                               100,
                               m_bulletSpeed,
                               0,
                               t_house,
                               m_point - Vec2(m_width * 0.5, 0) + Vec2(0, m_health * 0.7),
                               m_targetPoint + Vec2(0,m_health * 0.7)
                               );
            BulletManager::getInstance()->fire(bp);
        }
            break;
        case 3:     // 陆地 自爆
            
            break;
        case 4:     // 飞行 远程
        {
            m_status &= (~e_attack);
            BulletParameter bp(m_damage,
                               0,
                               1,
                               0,
                               0,
                               1,
                               100,
                               m_bulletSpeed,
                               0,
                               t_house,
                               m_point - Vec2(m_width * 0.5, 0) + Vec2(0, m_health * 0.7),
                               m_targetPoint + Vec2(0,m_health * 0.7)
                               );
            BulletManager::getInstance()->fire(bp);
        }
            break;
        default:
            break;
    }
}
// - 获得 基本 属性
string Enemy::getId()
{
    return m_id;
}
string Enemy::getMonsterName()
{
    return m_monsterName;
}
string Enemy::getModelId()
{
    return m_modelId;
}
int Enemy::getWidth()
{
    return m_width;
}
int Enemy::getHeight()
{
    return m_height;
}
int Enemy::getActionType()
{
    return m_actionType;
}
string Enemy::getBulletModelId()
{
    return m_bulletModelId;
}
int Enemy::getAttackType()
{
    return m_attackType;
}
float Enemy::getBulletSpeed()
{
    return m_bulletSpeed;
}
int Enemy::getLevel()
{
    return m_level;
}
int Enemy::getHealthValue()
{
    return m_health;
}
float Enemy::getHealthPercent()
{
    if (m_health < 0) {
        m_health = 0;
    }
    return m_health / m_totalHealth * 100.0f;
}
float Enemy::getSpeed()
{
    return m_speed;
}
float Enemy::getDamage()
{
    return m_damage;
}
float Enemy::getAttackSpeed()
{
    return m_attackSpeed;
}
int Enemy::getGoldForDied()
{
    return m_gold;
}
string Enemy::getDrop()
{
    return m_drop;
}

