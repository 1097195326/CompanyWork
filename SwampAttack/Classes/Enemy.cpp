//
//  Enemy.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "Enemy.h"


Enemy::Enemy(Json::Value data):m_data(data)
{
    m_id = m_data["Id"].asString();
    m_monsterName = m_data["MonsterName"].asString();
    m_modelId = m_data["ModelId"].asString();
    m_actionType = m_data["ActionType"].asString();
    m_level = m_data["Level"].asInt();
    m_health = m_data["Hp"].asInt();
    m_speed = Vec2(m_data["Speed"].asDouble(), 0);
    m_damage = m_data["Damage"].asDouble();
    m_attackSpeed = m_data["AttackSpeed"].asDouble();
    m_gold = m_data["Gold"].asInt();
    m_drop = m_data["Drop"].asString();
}
Enemy::~Enemy()
{
    
}
void Enemy::gameLoop(float data)
{
    
    
}

#pragma - get function

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

