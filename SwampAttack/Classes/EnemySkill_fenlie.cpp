//
//  EnemySkill_fenlie.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_fenlie.hpp"
#include "Enemy.h"
#include "EnemyManager.h"

EnemySkill_fenlie::EnemySkill_fenlie(string id):
EnemySkill(id),
isFenlie(false)
{
    
}
void EnemySkill_fenlie::run(float timeStep)
{
    if(m_enemy->getHealthPercent() <= m_hp && !isFenlie)
    {
        isFenlie = true;
        
        EnemyManager::getInstance()->getCurrectGroup()->pushEnemy(m_splitting,m_enemy->getPosition());
    }
}
