//
//  BulletManager.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#include "BulletManager.h"

BulletManager::BulletManager()
{
    
}
BulletManager::~BulletManager()
{
    
}
BulletManager * BulletManager::getInstance()
{
    static BulletManager _bulletManager;
    return &_bulletManager;
}
void BulletManager::fire(BulletParameter bp)
{
//    bp.m_num = 1;
    for (int i = 0; i < bp.m_num; ++i) {
        Bullet * bullet = new Bullet(bp);
        bullets.push_back(bullet);
    }
}
void BulletManager::gameLoop(float data)
{
    std::list<Bullet *>::iterator itr;
    for (itr = bullets.begin(); itr != bullets.end();) {
        Bullet * bullet = *itr;
        if (bullet->isCanDelete()) {
            bullets.erase(itr++);
            delete bullet;
        }else
        {
            ++itr;
            bullet->gameLoop(data);
        }
    }
}
void BulletManager::resetData()
{
    std::list<Bullet *>::iterator itr;
    for (itr = bullets.begin(); itr != bullets.end();) {
        Bullet * bullet = *itr++;
        delete bullet;
    }
    bullets.clear();
}
std::list<Bullet*> BulletManager::getBulletData()
{
    return bullets;
}