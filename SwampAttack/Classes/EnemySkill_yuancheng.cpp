//
//  EnemySkill_yuancheng.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_yuancheng.hpp"
#include "Enemy.h"
#include "BulletManager.h"


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
        m_enemy->setStateFarattack();
    }
}
void EnemySkill_yuancheng::doDone()
{
    BulletParameter bp(m_long,
                       0,
                       1,
                       0,
                       0,
                       1,
                       100,
                       100,
                       0,
                       1,
                       t_house,
                       m_enemy->getPosition() - Vec2(m_enemy->getWidth() * 0.5, 0) + Vec2(0, m_enemy->getHeight() * 0.65),
                       m_enemy->getTargetPosition() + Vec2(0,m_enemy->getHeight() * 0.55),
                       "100010"
                       );
    BulletManager::getInstance()->fire(bp);
}