//
//  EnemyGroup.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/7.
//
//

#include "EnemyGroup.h"
#include "ConfigManager.h"


EnemyGroup::EnemyGroup(Json::Value data):status(_isHave)
{
    setData(data);
    
}
EnemyGroup::~EnemyGroup()
{
    clearData();
}
void EnemyGroup::setData(Json::Value data)
{
    for (int i = 0; i < data.size(); ++i) {
        Json::Value d = data[i];
        string monsterid = d["monsterid"].asString();
        int     number = atoi(d["number"].asString().c_str());
        index[i] = number;
        for (int j = 0; j < number; ++j) {
            Json::Value enemyConfig = ConfigManager::getInstance()->getDataByTag("guaiwu",monsterid);
            Enemy * enemy = new Enemy(enemyConfig);
            enemyData[i] = enemy;
        }
    }
}
std::map<int,Enemy*> EnemyGroup::getEnemyData()
{
    return enemyData;
}
void EnemyGroup::clearData()
{
    for (int i = 0 ; i < enemyData.size(); ++i) {
        delete enemyData[i];
    }
}
void EnemyGroup::gameLoop(float data)
{
    if (status == _isDie) {
        return;
    }
    bool die = true;
    for (int i = 0 ; i < enemyData.size(); ++i) {
        if (!enemyData[i]->isDied())
        {
            die = false;
            enemyData[i]->gameLoop(data);
        }
    }
    if (die) {
        status = _isDie;
    }
}
bool EnemyGroup::isDie()
{
    return status == _isDie;
}