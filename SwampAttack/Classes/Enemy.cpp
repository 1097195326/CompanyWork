//
//  Enemy.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "Enemy.h"
#include "GameDirector.h"
#include "EnemySprite.h"
#include "GameMapManager.h"



Enemy::Enemy(Json::Value data):m_data(data)
{
    GameMap * gameMap = GameMapManager::getInstance()->getGameMap();
    m_point = gameMap->m_startPoint + Vec2(0, random(1, 10));
    m_targetPoint = gameMap->m_targetPoint;
    ///--- set status ---
    m_status = e_waiting;
    ///------set data-------
    m_id = m_data["Id"].asString();
    m_monsterName = m_data["MonsterName"].asString();
    m_modelId = m_data["ModelId"].asString();
    m_actionType = m_data["ActionType"].asString();
    m_level = atoi(m_data["Level"].asString().c_str());
    m_health = atoi(m_data["Hp"].asString().c_str());
    m_speed = Vec2(-atof(m_data["Speed"].asString().c_str()), 0);
    m_damage = atof(m_data["Damage"].asString().c_str());
    m_attackSpeed = atof(m_data["AttackSpeed"].asString().c_str());
    m_gold = atoi(m_data["Gold"].asString().c_str());
    m_drop = m_data["Drop"].asString();
    
    setView();
}
Enemy::~Enemy()
{
    
}
void Enemy::gameLoop(float data)
{
    if (m_status & e_die || m_status & e_dieing)
    {
        return;
    }
    if (m_status == e_waiting) {
        m_status &= e_clear;
        m_status |= e_walk;
    }
    if (m_status & e_walk)
    {
        m_point = m_point + m_speed * 0.1;
        if (m_targetPoint.x >= m_point.x) {
            m_status &= e_clear;
            m_status |= e_attack;
            
        }
    }
//    if (m_status & walk) {
//        log("%d",m_status);
//    }
//    if (m_status & attack) {
//        log("%d",m_status);
//    }
    
}
void Enemy::setView()
{
    EnemySprite * enemySprite = new EnemySprite("zombie");
    enemySprite->setMode(this);
    _G_D->addChild(enemySprite);
    
}
void Enemy::setRect(cocos2d::Rect _rect)
{
    m_rect = _rect;
}
bool Enemy::isContainsPoint(cocos2d::Vec2 point)
{
    return m_rect.containsPoint(point);
}
void Enemy::hurt(int damage)
{
    m_health = m_health - damage;
    if (m_health <= 0) {
        m_status &= e_clear;
        m_status |= e_dieing;
    }
    log("enemy health :%f",m_health);
}
//--- view 接口
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
    return m_status & e_hurt;
}
bool Enemy::isAttack()
{
    return m_status & e_attack;
}
bool Enemy::isDied()
{
    return m_status & e_die;
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
string Enemy::getActionType()
{
    return m_actionType;
}
int Enemy::getLevel()
{
    return m_level;
}
int Enemy::getHealthValue()
{
    return m_health;
}
Vec2 Enemy::getSpeed()
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

