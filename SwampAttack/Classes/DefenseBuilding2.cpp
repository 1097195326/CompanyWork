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
#include "Enemy.h"

DefenseBuilding2::DefenseBuilding2(Json::Value data):DefenseBuilding(data)
{
    
}
void DefenseBuilding2::setView()
{
    if (!m_isUnlock) {
        return;
    }
    DefenseBuildingSprite * sprite = new DefenseBuilding2_Sprite(this);
    sprite->autorelease();
}

void DefenseBuilding2::gameLoop(float data)
{
    if (!m_isUnlock)
    {
        return;
    }
    if (m_defenceType == 2 || m_defenceType == 3)
    {
        m_waitDelay += data;
        if (m_waitDelay >= 1 && m_state == d_wait)
        {
            m_waitDelay = 0.0f;
            m_state = d_canHurt;
        }else
        {
            m_state = d_wait;
        }
    }
}
void DefenseBuilding2::hurtEnemy(Enemy *enemy)
{
    enemy->hurt(m_damage);
}
