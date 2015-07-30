//
//  LiquidBullet.h
//  SwampAttack
//
//  Created by oceantech02 on 15/7/30.
//
//

#ifndef __SwampAttack__LiquidBullet__
#define __SwampAttack__LiquidBullet__

#include "Bullet.h"

class LiquidBullet : public Bullet
{
private:
    
public:
    LiquidBullet(BulletParameter bp);
    ~LiquidBullet();
    void    setView();
    void    gameLoop(float data);
    
};

#endif /* defined(__SwampAttack__LiquidBullet__) */
