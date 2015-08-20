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
    m_enemySet.clear();
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
//                    log("size:%d",(int)m_enemySet.size());
                    if (m_enemySet.size() >= m_bp.m_hurtNum) {
                        m_state = _b_arrive;
                        return;
                    }
                    std::set<Enemy *>::iterator iter = m_enemySet.find(enemy);
                    if (*iter != enemy) {
                        m_enemySet.insert(enemy);
                        enemy->hurt(m_damage,m_bp.m_underAttackAction);
                    }
//                    log("size2:%d",(int)m_enemySet.size());
                    
                }
            }
        }
    }
    if (m_state == _b_arrive) {
        
    }
}