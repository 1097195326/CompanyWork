//
//  PunctureBullet.h
//  SwampAttack
//
//  Created by oceantech02 on 15/7/28.
//
//

#ifndef __SwampAttack__PunctureBullet__
#define __SwampAttack__PunctureBullet__

#include "Bullet.h"
class Enemy;

class PunctureBullet : public Bullet
{
private:
    std::set<Enemy *> m_enemySet;
public:
    PunctureBullet(BulletParameter bp);
    ~PunctureBullet();
    
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__PunctureBullet__) */
