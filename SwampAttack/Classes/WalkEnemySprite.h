//
//  WalkEnemySprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#ifndef __SwampAttack__WalkEnemySprite__
#define __SwampAttack__WalkEnemySprite__

#include "EnemySprite.h"

class WalkEnemySprite : public EnemySprite {
private:
    
protected:
    void    wanderFont();
    void    wanderBack();
    void    move();
    void    attack();
    void    die();
    void    hurt();
    void    setArmorView();
public:
    void        update(float data);
    WalkEnemySprite(Enemy * model);
    void    showBuff();
};

#endif /* defined(__SwampAttack__WalkEnemySprite__) */
