//
//  DefenseBuilding4.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/8/7.
//
//

#include "DefenseBuilding4.h"
#include "House.h"
#include "DefenseBuilding4_Sprite.h"
#include "BuildingSpriteView.hpp"
#include "EnemyManager.h"
#include "GameMapManager.h"


DefenseBuilding4::DefenseBuilding4(Json::Value data):
DefenseBuilding(data),
canfire(false)
{
    
}
void DefenseBuilding4::setView()
{
    if (!m_isUnlock) {
        return;
    }
    DefenseBuildingSprite * sprite = new DefenseBuilding4_Sprite(this);
    sprite->autorelease();
    BuildingSpriteView * view = new BuildingSpriteView(this);
    view->autorelease();
    
    numberIndex = 0;
}

void DefenseBuilding4::gameLoop(float data)
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
                }
            }
        }
    }
    
}
void DefenseBuilding4::setStateCanhurt()
{
    DefenseBuilding::setStateCanhurt();
    numberIndex = 0;
}
void DefenseBuilding4::setStateHurting()
{
    DefenseBuilding::setStateHurting();
    canfire = true;
}
void DefenseBuilding4::hurtCall()
{
    ++numberIndex;
    if (numberIndex >= m_number)
    {
        canfire = false;
        setStateWait();
    }else
    {
        canfire = true;
    }
}
bool DefenseBuilding4::isInRange(Vec2 point)
{
    return _G_M_M->fightScene_tengman_point.x + 180 * numberIndex > point.x;
}
void DefenseBuilding4::hurtEnemy(Enemy *enemy)
{
    float e_f = enemy->getSpeedF();
    enemy->hurtJiansu(3.0f + e_f);
}
