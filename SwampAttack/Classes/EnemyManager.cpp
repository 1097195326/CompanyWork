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
    
}
void EnemyManager::clearData()
{
    
}
void EnemyManager::gameLoop(float data)
{
    
}