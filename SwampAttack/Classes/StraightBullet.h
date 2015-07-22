//
//  StraightBullet.h
//  SwampAttack
//
//  Created by oceantech02 on 15/7/22.
//
//

#ifndef __SwampAttack__StraightBullet__
#define __SwampAttack__StraightBullet__

#include "Bullet.h"


class StraightBullet : public Bullet
{
private:
    
    
public:
    StraightBullet(BulletParameter bp);
    ~StraightBullet();
    
    void move();
};

#endif /* defined(__SwampAttack__StraightBullet__) */
