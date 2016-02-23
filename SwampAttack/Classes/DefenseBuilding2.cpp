//
//  DefenseBuilding2.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/8.
//
//

#include "DefenseBuilding2.h"
#include "House.h"
#include "DefenseBuilding2_Sprite.h"
#include "BuildingSpriteView.hpp"
#include "EnemyManager.h"


DefenseBuilding2::DefenseBuilding2(Json::Value data):
DefenseBuilding(data),
canfire(false)
{
    
}
void DefenseBuilding2::setView()
{
    if (!m_isUnlock) {
        return;
    }
    DefenseBuildingSprite * sprite = new DefenseBuilding2_Sprite(this);
    sprite->autorelease();
    BuildingSpriteView * view = new BuildingSpriteView(this);
    view->autorelease();
    numberIndex = m_number;
}

void DefenseBuilding2::gameLoop(float data)
{
    if (!m_isUnlock)
    {
        return;
    }
    
//    m_waitDelay += data;
//    if (m_waitDelay >= 1 && m_state == d_wait)
//    {
//        m_waitDelay = 0.0f;
//        m_state = d_canHurt;
//    }else
//    {
//        m_state = d_wait;
//    }
    
}
void DefenseBuilding2::setStateCanhurt()
{
    DefenseBuilding::setStateCanhurt();
    numberIndex = m_number;
}
void DefenseBuilding2::hurtCall()
{
    --numberIndex;
    if (numberIndex <=0)
    {
        setStateWait();
    }
    EnemyGroup * enemyGroup = EnemyManager::getInstance()->getCurrectGroup();
    if (!enemyGroup)
    {
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
            }
        }
    }
}
void DefenseBuilding2::hurtEnemy(Enemy *enemy)
{
//    log("m_damage :%d",m_damage);
    enemy->hurt(m_damage);
}
