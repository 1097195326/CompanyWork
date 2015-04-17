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
void BulletManager::fire(BulletParameter bp, cocos2d::Vec2 toPosition)
{
    for (int i = 0; i < bp.m_num; ++i) {
        Bullet * bullet = new Bullet(bp,toPosition);
        bullets.push_back(bullet);
    }
}
void BulletManager::gameLoop(float data)
{
    std::list<Bullet *>::iterator itr;
    for (itr = bullets.begin(); itr != bullets.end(); itr++) {
        Bullet * bullet = *itr;
        bullet->gameLoop(data);
    }
}