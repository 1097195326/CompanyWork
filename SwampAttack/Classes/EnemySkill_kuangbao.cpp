//
//  EnemySkill_kuangbao.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_kuangbao.hpp"
#include "Enemy.h"

EnemySkill_kuangbao::EnemySkill_kuangbao(string id):
EnemySkill(id)
{
    
}
void EnemySkill_kuangbao::run(float timeStep)
{
//    log("run---:%f::%f",m_enemy->getHealthPercent(),m_hp);
    
    if(m_enemy->isWalk() && m_enemy->getHealthPercent() <= m_hp * 100)
    {
        m_enemy->effectSpeedByPer(m_accelerate);
    }
    
}