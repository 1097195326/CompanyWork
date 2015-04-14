//
//  BulletManager.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__BulletManager__
#define __SwampAttack__BulletManager__

#include "GameObject.h"
#include "Bullet.h"

class BulletManager : public GameObject {
private:
    std::list<Bullet*> bullets;
    
public:
    void fire(int num);
    
public:
    
    BulletManager();
    ~BulletManager();
    static BulletManager * getInstance();
    
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__BulletManager__) */
