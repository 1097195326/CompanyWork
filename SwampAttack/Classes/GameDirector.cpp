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
    BulletManager::getInstance()->gameLoop(data);
    
    checkCross();
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
void GameDirector::checkCross()
{
    EnemyGroup * enemyGroup = EnemyManager::getInstance()->getCurrectGroup();
    if (!enemyGroup) {
        return;
    }
    std::list<Enemy*> enemyData =enemyGroup->getEnemyData();
    std::list<Bullet*> bulletData = BulletManager::getInstance()->getBulletData();
    
    if (!bulletData.empty() && !enemyData.empty())
    {
        std::list<Bullet*>::iterator b_iter;
        std::list<Enemy*>::iterator e_iter;
        for (e_iter = enemyData.begin() ; e_iter != enemyData.end(); ++e_iter)
        {
            for (b_iter = bulletData.begin(); b_iter != bulletData.end(); ++b_iter)
            {
                Enemy * enemy = *e_iter;
                Bullet * bullet = *b_iter;
                Vec2 b_point = bullet->getPosition();
                if (bullet->isArrive() &&
                    !enemy->isDied() &&
                    enemy->isContainsPoint(b_point))
                {
                    enemy->hurt(bullet->getDamage());
                }
            }
        }
    }
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
void GameDirector::addChild(Node * node, int zOrder)
{
    if (gameFightLayer) {
        
        gameFightLayer->addChild(node,zOrder);
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