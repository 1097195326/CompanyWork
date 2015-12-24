//
//  EnemySkill.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/21.
//
//

#include "EnemySkill.hpp"
#include "Enemy.h"

EnemySkill::EnemySkill(string id)
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("enemySkill");
    Json::Value enemySkillData = propHelper->getJsonData();
    Json::Value data = enemySkillData[id];
    
    m_id = data["ID"].asString();
    m_idName = data["IDName"].asString();
    m_type = atoi(data["Type"].asString().c_str());
    m_hp = atof(data["Hp"].asString().c_str());
    m_time = atof(data["Time"].asString().c_str());
    m_probablillity = atof(data["Probability"].asString().c_str());
    m_accelerate = atof(data["Accelerate"].asString().c_str());
    m_defense = atof(data["Defense"].asString().c_str());
    m_long = atof(data["Long"].asString().c_str());
    m_dodge = atof(data["Dodge"].asString().c_str());
    
    m_splitting = data["Splitting"];
    m_call = data["Call"];
    
}
void EnemySkill::setEnemy(Enemy *enemy)
{
    m_enemy = enemy;
}
void EnemySkill::run(float timeStep)
{
    
}