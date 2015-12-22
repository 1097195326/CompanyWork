//
//  EnemySkill_zhaohuan.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_zhaohuan.hpp"
#include "WalkEnemy.h"
#include "FlyEnemy.h"
#include "EnemyManager.h"


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
        m_timeStep = 0.0f;
        for (int i = 0; i < m_call.size(); ++i) {
            Json::Value d = m_call[i];
            string monsterid = d["monsterid"].asString();
            int     number = atoi(d["number"].asString().c_str());
            
            for (int j = 0; j < number; ++j) {
                Json::Value enemyConfig = ConfigManager::getInstance()->getDataByTag("guaiwu",monsterid);
                int actionType = atoi(enemyConfig["ActionType"].asString().c_str());
                Enemy * enemy = NULL; //new Enemy(enemyConfig);
                switch (actionType) {
                    case 1:
                        enemy = new WalkEnemy(enemyConfig);
                        break;
                    case 2:
                        enemy = new FlyEnemy(enemyConfig);
                        break;
                    default:
                        enemy = new WalkEnemy(enemyConfig);
                        break;
                }
                EnemyManager::getInstance()->getCurrectGroup()->pushEnemy(enemy);
            }
        }
    }
}
