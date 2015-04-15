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
    m_point = gameMap->m_startPoint;
    m_targetPoint = gameMap->m_targetPoint;
    ///--- set status ---
    m_status = walk;
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
    if (m_status & die || m_status & dieing)
    {
        return;
    }
    if (m_status & walk)
    {
        m_point = m_point + m_speed * 0.1;
//        if (m_targetPoint.x >= m_point.x) {
//            m_status &= clear;
//            m_status |= attack;
//        }
    }
    
    
}
void Enemy::setView()
{
    EnemySprite * enemySprite = new EnemySprite("zombie");
    enemySprite->setPosition(Vec2(100,100));
    enemySprite->setMode(this);
    _G_D->addChild(enemySprite);
    
}
#pragma - get function
bool Enemy::isDieing()
{
    return m_status & dieing;
}
bool Enemy::isWalk()
{
    return m_status & walk;
}
bool Enemy::isHurt()
{
    return m_status & hurt;
}
bool Enemy::isAttack()
{
    return m_status & attack;
}
Vec2 Enemy::getPosition()
{
    return m_point;
}
Vec2 Enemy::getTargetPosition()
{
    return m_targetPoint;
}
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

