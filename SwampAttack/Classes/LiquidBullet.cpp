//
//  LiquidBullet.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/7/30.
//
//

#include "LiquidBullet.h"
#include "EnemyManager.h"
#include "House.h"
#include "FireBulletSprite.h"


LiquidBullet::LiquidBullet(BulletParameter bp):Bullet(bp)
{
    
}
LiquidBullet::~LiquidBullet()
{
    
}
void LiquidBullet::setView()
{
    log("fire bullet sprite");
    FireBulletSprite * sprite = new FireBulletSprite();
    sprite->setModel(this);
    sprite->setRotation(m_angle);
    sprite->autorelease();
}
void LiquidBullet::gameLoop(float data)
{
    if (m_state == _b_moving)
    {
        
        move();
        if (m_Point.distanceSquared(m_StartPoint) >= m_toPoint.distanceSquared(m_StartPoint))
        {
            m_state = _b_arrive;
            return;
        }
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
                Rect b_rect = getRect();
                if (isFireEnemy() &&
                    !enemy->isDied() &&
                    enemy->isContainsPoint(b_rect))
                {
                    enemy->hurt(m_damage,m_bp.m_underAttackAction);
                }
            }
        }
        
    }
    if (m_state == _b_arrive) {
        
    }
}