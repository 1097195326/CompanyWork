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


GameDirector::GameDirector()
{
    gameMap = GameMapManager::getInstance()->getGameMap();
    
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(GameDirector::gameLoop), this, 1/60, false);
    
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
        GameOverStatus status;
        if (House::getInstance()->isOver()) {
            status = o_loss;
        }else
        {
            status = o_win;
        }
        Director::getInstance()->replaceScene(GameOverScene::scene(status));
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
//    std::list<Bullet*> bulletData = BulletManager::getInstance()->getBulletData();
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
//            if (!bulletData.empty())
//            {
//                for (b_iter = bulletData.begin(); b_iter != bulletData.end(); ++b_iter)
//                {
//                    
//                    Bullet * bullet = *b_iter;
//                    Rect b_rect = bullet->getRect();
//                    if (bullet->isArrive() &&
//                        bullet->isFireEnemy() &&
//                        !enemy->isDied() &&
//                        enemy->isContainsPoint(b_rect))
//                    {
//                        enemy->hurt(bullet->getDamage(),bullet->getAttackIndex());
//                    }else if (bullet->isArrive() && bullet->isFireHouse())
//                    {
//                        House::getInstance()->hurt(bullet->getDamage());
//                    }
//                }
//            }
        
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
void GameDirector::startGame()
{
    clearStatus();
    m_status |= s_run ;
}
void GameDirector::restartGame()
{
    clearStatus();
    m_status |= s_run ;
    
    EnemyManager::getInstance()->reStartGame();
    
}
void GameDirector::overGame()
{
    EnemyManager::getInstance()->overGame();
    
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

bool GameDirector::isOver()
{
    return m_status & s_over;
}
void GameDirector::clearStatus()
{
    m_status &= s_clear;
}