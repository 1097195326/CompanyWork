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
    float   dlay;
protected:
    void    wanderFont();
    void    wanderBack();
    void    move();
    void    shanbi();
    void    attack(float data);
    void    die();
    void    hurt();
    void    dianji();
    void    tanfei();
    void    zhaohuan();
    void    rebirth();
    void    fenlie();
    void    yuancheng();
    void    setArmorView();
    
public:
    void        update(float data);
    WalkEnemySprite(Enemy * model);
    void    showBuff();
};

#endif /* defined(__SwampAttack__WalkEnemySprite__) */
