//
//  EnemySkill_zhaohuan.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_zhaohuan.hpp"
#include "EnemyManager.h"
#include "Enemy.h"

EnemySkill_zhaohuan::EnemySkill_zhaohuan(string id):
EnemySkill(id),
m_timeStep(0.0f)
{
    
}
void EnemySkill_zhaohuan::run(float timeStep)
{
    m_timeStep += timeStep;
    
    if (m_timeStep >= m_time)
    {
//        log("zhao huan");
        m_timeStep = 0.0f;
        m_enemy->setStateZhaohuan();
        EnemyManager::getInstance()->getCurrectGroup()->pushEnemy(m_call,m_enemy->getPosition());
    }
}
