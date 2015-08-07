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
#include "Enemy.h"

DefenseBuilding4::DefenseBuilding4(Json::Value data):DefenseBuilding(data)
{
    
}
void DefenseBuilding4::setView()
{
    if (!m_isUnlock) {
        return;
    }
    DefenseBuildingSprite * sprite = new DefenseBuilding4_Sprite(this);
    sprite->autorelease();
}

void DefenseBuilding4::gameLoop(float data)
{
    if (!m_isUnlock)
    {
        return;
    }
    if (m_defenceType == 2 || m_defenceType == 3)
    {
        m_index += data;
        if (m_index >= 1 && m_state == d_wait)
        {
            m_index = 0;
            m_state = d_canHurt;
        }else
        {
            m_state = d_wait;
        }
    }
}
void DefenseBuilding4::hurtEnemy(Enemy *enemy)
{
    enemy->hurtJiansu(m_deceleration);
}
