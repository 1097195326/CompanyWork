//
//  DefenseBuilding3.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/8.
//
//

#include "DefenseBuilding3.h"
#include "DefenseBuilding3_Sprite.h"
#include "BuildingSpriteView.hpp"
#include "BulletManager.h"
#include "EnemyManager.h"


DefenseBuilding3::DefenseBuilding3(Json::Value data):
DefenseBuilding(data),
canfire(false)
{
    fireEnemy = NULL;
    numberIndex = m_number;
    
    if (m_jishu >= m_deadnumber)
    {
        setStateCanhurt();
    }else
    {
        setStateWait();
    }
}
void DefenseBuilding3::setView()
{
    if (!m_isUnlock) {
        return;
    }
    DefenseBuildingSprite * sprite = new DefenseBuilding3_Sprite(this);
    sprite->autorelease();
    BuildingSpriteView * view = new BuildingSpriteView(this);
    view->autorelease();
    
}

void DefenseBuilding3::gameLoop(float data)
{
    if (!m_isUnlock)
    {
        return;
    }
    
//    if(m_state == d_hurting)
//    {
//        m_waitDelay += data;
//        if (m_waitDelay >= 0.8)
//        {
//            m_waitDelay = 0;
//            hurtingDelay = false;
//        }
//    }
    if (canfire)
    {
        
        EnemyGroup * enemyGroup = EnemyManager::getInstance()->getCurrectGroup();
        if (!enemyGroup) {
            return;
        }
        std::list<Enemy*> enemyData =enemyGroup->getShowEnemyData();
        
        if (!enemyData.empty())
        {
            std::list<Enemy*>::iterator e_iter;
            
            for (e_iter = enemyData.begin() ; e_iter != enemyData.end(); ++e_iter)
            {
                Enemy * enemy = *e_iter;
                
                if (!(enemy->isDieing() || enemy->isDied() || enemy->isCanDelete()) &&
                    isInRange(enemy->getPosition()) &&
                    enemy->getActionType() == 1)
                {
                    hurtEnemy(enemy);
                    break;
                }
            }
        }
    }
    
}
void DefenseBuilding3::setStateCanhurt()
{
    DefenseBuilding::setStateCanhurt();
    numberIndex = m_number;
}
void DefenseBuilding3::setStateHurting()
{
    canfire = true;
}
void DefenseBuilding3::hurtEnemy(Enemy *enemy)
{
    DefenseBuilding::setStateHurting();
    canfire = false;
    fireEnemy = enemy;
}
void DefenseBuilding3::hurtCall()
{
    
    if (!fireEnemy ) { // || fireEnemy->isDied() || fireEnemy->isCanDelete()
        return;
    }
    --numberIndex;
    if (numberIndex <=0)
    {
        canfire = false;
        setStateWait();
    }else
    {
        canfire = true;
    }
//    log("fire enemy x:%f",fireEnemy->getPosition().x);
    GameMap * map = GameMapManager::getInstance()->getGameMap();
    BulletParameter bp(m_damage,
                       0,
                       1,
                       0,
                       0,
                       1,
                       m_damageArea,
                       120,
                       1,
                       1,
                       t_enemy,
                       map->gangpao_BulletStartPoint,
                       (fireEnemy->getPosition() + Vec2(0,fireEnemy->getHeight() * 0.4)),
                       m_bulletModelId
                       );
    BulletManager::getInstance()->fire(bp);

    fireEnemy = NULL;
}