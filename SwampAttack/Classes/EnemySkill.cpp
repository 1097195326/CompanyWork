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
    std::map<int,std::string> m_hashHead = propHelper->getHashHead();
    Json::Value data = propHelper->getJsonData();
    
    
    
}
void EnemySkill::setEnemy(Enemy *enemy)
{
    m_enmey = enemy;
}
void EnemySkill::run(float timeStep)
{
    
}