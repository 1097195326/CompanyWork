//
//  DefenseBuilding3.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/6/8.
//
//

#include "DefenseBuilding3.h"
#include "House.h"
#include "DefenseBuilding3_Sprite.h"
#include "BulletManager.h"
#include "Enemy.h"

DefenseBuilding3::DefenseBuilding3(Json::Value data):DefenseBuilding(data)
{
    fireEnemy = NULL;
}
void DefenseBuilding3::setView()
{
    if (!m_isUnlock) {
        return;
    }
    DefenseBuildingSprite * sprite = new DefenseBuilding3_Sprite(this);
    sprite->autorelease();
}

void DefenseBuilding3::gameLoop(float data)
{
    if (!m_isUnlock)
    {
        return;
    }
    if (m_defenceType == 2 || m_defenceType == 3)
    {
        if(m_state == d_wait)
        {
            m_index += data;
            if (m_index >= 1)
            {
                m_index = 0;
                m_state = d_canHurt;
            }
        }
    }
}
void DefenseBuilding3::hurtEnemy(Enemy *enemy)
{
    m_state = d_hurting;
    
    fireEnemy = enemy;
}
void DefenseBuilding3::hurtCall()
{
    if (!fireEnemy ) { // || fireEnemy->isDied() || fireEnemy->isCanDelete()
        return;
    }
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
                       t_enemy,
                       map->gangpao_BulletStartPoint,
                       (fireEnemy->getPosition() + Vec2(0,fireEnemy->getHeight() * 0.4)),
                       "monkeyShell.png"
                       );
    BulletManager::getInstance()->fire(bp);

    fireEnemy = NULL;
}