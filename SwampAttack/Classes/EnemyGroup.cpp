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
            enemyData.push_back(enemy);
        }
    }
}
std::list<Enemy*> EnemyGroup::getEnemyData()
{
    return enemyData;
}
void EnemyGroup::clearData()
{
    std::list<Enemy*>::iterator iter;
    for (iter = enemyData.begin() ; iter != enemyData.end();)
    {
        Enemy * enemy = *iter;
        enemyData.erase(iter++);
        delete enemy;
    }
}
void EnemyGroup::gameLoop(float data)
{
    if (status == _isDie) {
        return;
    }
    bool die = true;
    std::list<Enemy*>::iterator iter;
    for (iter = enemyData.begin() ; iter != enemyData.end(); )
    {
        Enemy * enemy = *iter;
        if (enemy->isCanDelete())
        {
            enemyData.erase(iter++);
            delete enemy;
        }else
        {
            die = false;
            enemy->gameLoop(data);
            ++iter;
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