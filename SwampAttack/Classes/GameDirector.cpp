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
#include "House.h"
#include "DefenseBuildingManager.h"
#include "PropManager.h"
#include "GameOverScene.h"
#include "GameBuffManager.h"

#include "GameFightScene.h"

GameDirector::GameDirector()
{
    gameMap = GameMapManager::getInstance()->getGameMap();
    
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(GameDirector::gameLoop), this, 1/30, false);
    
    m_goldNum = 0;
    stopGame();
    
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
void GameDirector::initGameView()
{
    
    House::getInstance()->setView();
    DefenseBuildingManager::getInstance()->setView();
    Human::getInstance()->setView();
    GunManager::getInstance()->setFightView();
    PropManager::getInstance()->setFightView();
    EnemyManager::getInstance()->setView();
    
}
void GameDirector::addGold(int gold)
{
    m_goldNum += gold;
    notify();
}
int GameDirector::getGoldNum()
{
    return m_goldNum;
}
void GameDirector::gameLoop(float data)
{
//    log("game loop ----");
    if (m_status & s_over) {
        
        return;
    }
    if (m_status & s_stop)
    {
        return;
    }
    GameBuffManager::getInstance()->gameLoop(data);
    EnemyManager::getInstance()->gameLoop(data);
    Human::getInstance()->gameLoop(data);
    BulletManager::getInstance()->gameLoop(data);
    DefenseBuildingManager::getInstance()->gameLoop(data);
    PropManager::getInstance()->gameLoop(data);
    
    checkCross();
    if (EnemyManager::getInstance()->isOver() || House::getInstance()->isOver()) {
        clearStatus();
        m_status |= s_over;
        
        if (House::getInstance()->isOver()) {
            m_overStatus = o_loss;
        }else
        {
            m_overStatus = o_win;
        }
        notify();
//        resetGameData();
//        overGame();
    }
}
void GameDirector::onTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Human::getInstance()->fire(touch, event);
}
void GameDirector::onTouchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Human::getInstance()->fire(touch, event);
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
    std::map<string,DefenseBuilding *> buildingData = DefenseBuildingManager::getInstance()->getBuildingData();
    
    if (!enemyData.empty())
    {
        std::list<Bullet*>::iterator b_iter;
        std::list<Enemy*>::iterator e_iter;
        std::map<string,DefenseBuilding *>::iterator d_iter;
        
        for (e_iter = enemyData.begin() ; e_iter != enemyData.end(); ++e_iter)
        {
            Enemy * enemy = *e_iter;
            // bullet
        
            // defense
            if (!buildingData.empty())
            {
                for (d_iter = buildingData.begin(); d_iter != buildingData.end(); ++d_iter)
                {
                    DefenseBuilding * building = d_iter->second;
                    if (building->isCanHurt() &&
                        building->isInRange(enemy->getPosition()) &&
                        enemy->getActionType() == 1)
                    {
                        switch (building->getDefenceType())
                        {
                            case 2:
                            case 3:
                                building->hurtEnemy(enemy);
//                                 building->fire(Vec2(enemy->getPosition().x,
//                                                     enemy->getPosition().y + enemy->getHeight() * 0.5));
                                
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            
        }
    }
}
void GameDirector::resetGameData()
{
    House::getInstance()->resetData();
    GunManager::getInstance()->resetData();
    BulletManager::getInstance()->resetData();
    GameBuffManager::getInstance()->resetData();
    Human::getInstance()->resetData();
    
    EnemyManager::getInstance()->resetData();
    m_goldNum = 0;
}
void GameDirector::reliveGame()
{
    House::getInstance()->reliveGame();
}
void GameDirector::startGame()
{
    clearStatus();
    m_status |= s_run ;
}
void GameDirector::continueGame()
{
    clearStatus();
    m_status |= s_run;
}
void GameDirector::stopGame()
{
    clearStatus();
    m_status |= s_stop ;
}
GameOverStatus GameDirector::getOverStatus()
{
    return m_overStatus;
}
bool GameDirector::isOver()
{
    return m_status & s_over;
}
void GameDirector::clearStatus()
{
    m_status &= s_clear;
}