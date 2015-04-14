//
//  GameDirector.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#include "GameDirector.h"
#include "EnemyManager.h"
#include "Human.h"


GameDirector::GameDirector()
{
    log("game director gou zao ");
    gameMap = GameMapManager::getInstance()->getGameMap();
    schedule(CC_SCHEDULE_SELECTOR(GameDirector::gameLoop), 1/60);
    
    
    
}
GameDirector::~GameDirector()
{
    log("game director xi gou ");
}
GameDirector * GameDirector::getInstance()
{
    static GameDirector gameDirector;
    return &gameDirector;
}
void GameDirector::gameLoop(float data)
{
//    if (m_status & s_stop) {
//        return;
//    }
    log("%f",data);
    
    
}
void GameDirector::setGameLayer(cocos2d::Layer *layer)
{
    gameFightLayer = layer;
}
void GameDirector::start()
{
    m_status &= ~s_stop;
    m_status &= s_run ;
}
void GameDirector::stop()
{
    m_status &= ~s_run;
    m_status &= s_stop ;
}
void GameDirector::clearStatus()
{
    m_status &= s_clear;
}