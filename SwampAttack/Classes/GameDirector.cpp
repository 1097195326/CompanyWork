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
#include "BulletManager.h"


GameDirector::GameDirector()
{
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
    if (m_status & s_stop)
    {
        return;
    }
    EnemyManager::getInstance()->gameLoop(data);
    Human::getInstance()->gameLoop(data);
    
    
}
void GameDirector::onTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Human::getInstance()->fire(touch, event);
}
void GameDirector::onTouchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}
void GameDirector::onTouchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Human::getInstance()->stop();
}
void GameDirector::setGameLayer(Layer *layer)
{
    if (layer) {
        log("layer is true");
    }
    gameFightLayer = layer;
}
Layer * GameDirector::getGameLayer()
{
    return gameFightLayer;
}
void GameDirector::addChild(Node * node)
{
    if (gameFightLayer) {
        
        gameFightLayer->addChild(node);
    }else
    {
        log("jia");
    }
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