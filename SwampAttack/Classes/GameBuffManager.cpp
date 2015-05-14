//
//  GameBuffManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/5/14.
//
//

#include "GameBuffManager.h"

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
void GameBuffManager::addBuff(GameBuff * buff)
{
    m_buffData.push_back(buff);
}
void GameBuffManager::gameLoop(float data)
{
    if (m_buffData.size() == 0) {
        return;
    }
    m_dlay += data;
    if (m_dlay > 1)
    {
        m_dlay = 0;
    }else
    {
        return;
    }
    
    
}