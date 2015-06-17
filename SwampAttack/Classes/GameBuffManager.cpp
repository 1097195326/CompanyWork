//
//  GameBuffManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#include "GameBuffManager.h"
#include "ConfigManager.h"


GameBuffManager::GameBuffManager():m_dlay(0.0f)
{
    
}
GameBuffManager::~GameBuffManager()
{
    
}
GameBuffManager * GameBuffManager::getInstance()
{
    static GameBuffManager manager;
    return &manager;
}
GameBuff *  GameBuffManager::addBuff(string buffId)
{
    GCCsvHelper * propHelper = _C_M->getCsvHelperByName("daojubuff");
    Json::Value data = propHelper->getJsonData();
    GameBuff * buff = new GameBuff(data[buffId]);
    m_buffData.push_back(buff);
    return buff;
}
void GameBuffManager::resetData()
{
    std::list<GameBuff *>::iterator iter;
    for (iter = m_buffData.begin(); iter != m_buffData.end();)
    {
        GameBuff * buff = *iter++;
        delete buff;
    }
    m_buffData.clear();
}
void GameBuffManager::gameLoop(float data)
{
    std::list<GameBuff *>::iterator iter;
    for (iter = m_buffData.begin(); iter != m_buffData.end();)
    {
        GameBuff * buff = *iter;
        if (buff->isCanDelete()) {
            delete buff;
            m_buffData.erase(iter++);
        }else
        {
            iter++;
            buff->gameLoop(data);
        }
    }
//    log("buff manager size :%d",(int)m_buffData.size());
    
}