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
    void    move();
    void    attack();
    void    die();
    void    hurt();
public:
    void        update(float data);
    WalkEnemySprite(string name,Enemy * model);
};

#endif /* defined(__SwampAttack__WalkEnemySprite__) */
