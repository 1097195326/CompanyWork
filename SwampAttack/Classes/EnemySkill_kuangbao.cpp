//
//  EnemySkill_kuangbao.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_kuangbao.hpp"

EnemySkill_kuangbao::EnemySkill_kuangbao(string id):
EnemySkill(id)
{
    
}
void EnemySkill_kuangbao::run(float timeStep)
{
    if(m_enemy->getHealthPercent() <= m_hp)
    {
        m_enemy->effectSpeedByPer(m_accelerate);
    }
    
}