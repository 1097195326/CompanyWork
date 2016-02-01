//
//  EnemySkill_shanbi.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_shanbi.hpp"
#include "Enemy.h"

EnemySkill_shanbi::EnemySkill_shanbi(string id):
EnemySkill(id),
m_step(0.0f)
{
    
}
void EnemySkill_shanbi::run(float timeStep)
{
    if (m_enemy->isShanbi())
    {
        m_step += timeStep;
        log("shan bi m_step:%f",m_step);
        if (m_step >= m_dodge) {
            m_step = 0.0f;
            m_enemy->setStateWalk();
        }
    }
}