//
//  EnemySkill_fangyu.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_fangyu.hpp"
#include "Enemy.h"

EnemySkill_fangyu::EnemySkill_fangyu(string id):
EnemySkill(id)
{
    
}
void EnemySkill_fangyu::run(float timeStep)
{
    if (m_enemy->isFangyu())
    {
        m_step += timeStep;
        if (m_step >= m_defense) {
            m_step = 0.0f;
            m_enemy->setStateWalk();
        }
    }
}
