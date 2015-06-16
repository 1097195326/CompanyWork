//
//  EnemyGroup.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/7.
//
//

#include "EnemyGroup.h"
#include "ConfigManager.h"
#include "FlyEnemy.h"
#include "WalkEnemy.h"


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
//    log("%s",data.toStyledString().c_str());
    enemy_index = 0;
    isLastIndex = false;
    delay = 0.0f;
    
    for (int i = 0; i < data.size(); ++i) {
        Json::Value d = data[i];
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
    for (iter = show_enemyData.begin() ; iter != show_enemyData.end(); )
    {
        Enemy * enemy = *iter;
        if (enemy->isCanDelete())
        {
            show_enemyData.erase(iter++);
        }else
        {
            die = false;
            enemy->gameLoop(data);
            ++iter;
        }
    }
    if (die && isLastIndex) {
        status = _isDie;
//        log("enemy group %d",enemy_index);
    }
    if (!isLastIndex)
    {
        delay += data;
        if (delay >= 1)
        {
            delay = 0.0f;
            std::list<Enemy*>::iterator iter = enemyData.begin();
            for (int i = 0; i < enemy_index; i++) {
                iter++;
            }
            Enemy * enemy = *iter;
            enemy->setView();
            enemy_index++;
            show_enemyData.push_back(enemy);
            if (enemy_index == enemyData.size())
            {
                isLastIndex = true;
            }
        }
    }
    
}
bool EnemyGroup::isDie()
{
    return status == _isDie;
}