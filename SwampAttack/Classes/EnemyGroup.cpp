//
//  EnemyGroup.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/7.
//
//

#include "EnemyGroup.h"
#include "ConfigManager.h"


EnemyGroup::EnemyGroup(Json::Value data):status(isHave)
{
    
}
EnemyGroup::~EnemyGroup()
{
    
}
void EnemyGroup::setData(Json::Value data)
{
    for (int i = 0; i < data.size(); ++i) {
        Json::Value d = data[i];
        string monsterid = d["monsterid"].asString();
        int     number = d["number"].asInt();
        index[i] = number;
        for (int j = 0; j < number; ++j) {
            Json::Value enemyData = ConfigManager::getInstance()->getDataByTag("guaiwu",monsterid);
            Enemy * enemy = new Enemy(enemyData);
            enemyData[i] = enemy;
        }
        
    }
}
void EnemyGroup::clearData()
{
    for (int i = 0 ; i < enemyData.size(); ++i) {
        delete enemyData[i];
    }
}
void EnemyGroup::gameLoop(float data)
{
    for (int i = 0 ; i < enemyData.size(); ++i) {
        enemyData[i]->gameLoop(data);
    }
}