//
//  EnemySkill_fenlie.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/12/22.
//
//

#include "EnemySkill_fenlie.hpp"
#include "WalkEnemy.h"
#include "FlyEnemy.h"
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
