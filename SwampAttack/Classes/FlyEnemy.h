//
//  FlyEnemy.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#ifndef __SwampAttack__FlyEnemy__
#define __SwampAttack__FlyEnemy__

#include "Enemy.h"

class FlyEnemy : public Enemy {
private:
    Vec2    nextPoint;
    
protected:
    virtual void    move();
public:
    
    virtual void    setView();
public:
    FlyEnemy(Json::Value data);
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__FlyEnemy__) */
