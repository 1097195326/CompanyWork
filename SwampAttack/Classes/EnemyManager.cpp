//
//  EnemyManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemyManager.h"
#include "EnemyProgressBar.h"


EnemyManager::EnemyManager() : currentIndex(0)
{
    
}
EnemyManager::~EnemyManager()
{
    clearData();
}
EnemyManager * EnemyManager::getInstance()
{
    static EnemyManager manager;
    
    return &manager;
}
void EnemyManager::setData(Json::Value data)
{
    clearData();
    
    for (int i = 0; i < data.size(); ++i)
    {
        EnemyGroup * group = new EnemyGroup(data[i]);
        m_map[i] = group;
    }
    m_isOver = false;
}
EnemyGroup * EnemyManager::getCurrectGroup()
{
    return currentGroup;
}
void EnemyManager::clearData()
{
    if (m_map.size() > 0)
    {
        for (int i = 0; i < m_map.size(); ++i)
        {
            delete m_map[i];
        }
        m_map.clear();
    }
}
static float dley = 0;
void EnemyManager::gameLoop(float data)
{
    if (currentGroup)
    {
        if (currentGroup->isDie())
        {
            currentGroup = NULL;
            ++currentIndex;
            return;
        }
        currentGroup->gameLoop(data);
    }else
    {
        dley+=data;
        if (dley > 2)
        {
            dley = 0;
            if (currentIndex < m_map.size())
            {
                currentGroup = m_map[currentIndex];
                notify();
            }else
            {
//                log("Game Over");
                m_isOver = true;
            }
        }
    }
}
float EnemyManager::getEnemyProgress()
{
    return (float)(currentIndex+1) / (float )m_map.size() * 100;
}
bool EnemyManager::isOver()
{
    return m_isOver;
}
void EnemyManager::setView()
{
    EnemyProgressBar * bar = new EnemyProgressBar();
    bar->setSubject(this);
    bar->autorelease();
}