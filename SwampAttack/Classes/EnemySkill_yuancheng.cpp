//
//  EnemySkill_yuancheng.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_yuancheng.hpp"
#include "Enemy.h"

EnemySkill_yuancheng::EnemySkill_yuancheng(string id):
EnemySkill(id)
{
    
}
void EnemySkill_yuancheng::run(float timeStep)
{
    m_timeStep += timeStep;
    if (m_timeStep >= m_time)
    {
        m_timeStep = 0.0f;
        
    }
}
