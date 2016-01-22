//
//  EnemyManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "EnemyManager.h"
#include "EnemyProgressBar.h"
#include "GuanQiaManager.h"


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
void EnemyManager::resetData()
{
    currentIndex = 0;
    currentGroup = NULL;
    m_isOver = true;
//    clearData();
}
void EnemyManager::setData(Json::Value data)
{
    clearData();
    currentIndex = 0;
    currentGroup = NULL;
    m_isOver = false;
//    log("enemy data:%s",data.toStyledString().c_str());
    for (int i = 0; i < data.size(); ++i)
    {
        EnemyGroup * group = new EnemyGroup(data[i]);
        m_map[i] = group;
    }
    
}
EnemyGroup * EnemyManager::getCurrectGroup()
{
    return currentGroup;
}
void EnemyManager::clearData()
{
//    std::map<int,EnemyGroup *>::iterator iter;
//    for (iter = m_map.begin(); iter != m_map.end();)
//    {
//        EnemyGroup * group = iter->second;
//        delete group;
//        iter++;
//    }
//    m_map.clear();
    if (m_map.size() > 0)
    {
        for (int i = 0; i < m_map.size();)
        {
//            log("enemy manager clear");
            delete m_map[i++];
        }
        m_map.clear();
    }
}
void EnemyManager::stopGame()
{
    if (currentGroup)
    {
        currentGroup->stopGame();
    }
}
void EnemyManager::continueGame()
{
    if (currentGroup)
    {
        currentGroup->continueGame();
    }
}
static float dley = 0;
void EnemyManager::gameLoop(float data)
{
    if (m_isOver)
    {
        return;
    }
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
        if (dley > 1.0)
        {
            dley = 0;
            if (currentIndex < m_map.size())
            {
                currentGroup = m_map[currentIndex];
                notify();
            }else
            {
//                log("EnemyManager Game Over");
                resetData();
                GuanqiaModel * guanqiaModel = GuanQiaManager::getInstance()->getCurrentGuanqia();
                std::string dropId = guanqiaModel->getDropId();
                if (dropId.size() > 0)
                {
                    
                }
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