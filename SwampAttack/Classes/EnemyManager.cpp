//
//  EnemyManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
    
}
EnemyManager::~EnemyManager()
{
    
}
EnemyManager * EnemyManager::getInstance()
{
    static EnemyManager manager;
    
    return &manager;
}
void EnemyManager::setData(Json::Value data)
{
    for (int i = 0; i < data.size(); ++i) {
        EnemyGroup * group = new EnemyGroup(data[i]);
        m_map[i] = group;
    }
    
}
void EnemyManager::clearData()
{
    for (int i = 0; i < m_map.size(); ++i) {
        delete m_map[i];
    }
    m_map.clear();
}
void EnemyManager::gameLoop(float data)
{
    currentGroup->gameLoop(data);
}