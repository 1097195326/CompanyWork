//
//  FlyEnemySprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#ifndef __SwampAttack__FlyEnemySprite__
#define __SwampAttack__FlyEnemySprite__

#include "EnemySprite.h"

class FlyEnemySprite : public EnemySprite {
private:
    
protected:
    void    move();
    void    attack();
    void    die();
    void    dianji();
//    void    hurt();
    void    setArmorView();
public:
    void        update(float data);
    FlyEnemySprite(Enemy * model);
};

#endif /* defined(__SwampAttack__FlyEnemySprite__) */
