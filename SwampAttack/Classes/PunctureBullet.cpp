//
//  PunctureBullet.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/7/28.
//
//

#include "PunctureBullet.h"
#include "EnemyManager.h"
#include "House.h"

PunctureBullet::PunctureBullet(BulletParameter bp):Bullet(bp)
{
    
}
PunctureBullet::~PunctureBullet()
{
    
}
void PunctureBullet::gameLoop(float data)
{
    if (m_state == _b_moving)
    {
        
        move();
        if (m_Point.y > m_visibleOrigin.y + m_visibleSize.height ||
            m_Point.y < m_visibleOrigin.y ||
            m_Point.x < m_visibleOrigin.x ||
            m_Point.x > m_visibleOrigin.x + m_visibleSize.width)
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
            int num = 0;
            std::list<Enemy*>::iterator e_iter;
            for (e_iter = enemyData.begin() ; e_iter != enemyData.end(); ++e_iter)
            {
                Enemy * enemy = *e_iter;
                Rect b_rect = getRect();
                if (isFireEnemy() &&
                    !enemy->isDied() &&
                    enemy->isContainsPoint(b_rect)
                    )
                {
                    if (num >= m_bp.m_hurtNum) {
                        m_state = _b_arrive;
                        return;
                    }
                    ++num;
                    enemy->hurt(m_damage,m_bp.m_underAttackAction);
                }
            }
        }
    }
    if (m_state == _b_arrive) {
        
    }
}