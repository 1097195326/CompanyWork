//
//  CrumpEnemySprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/26.
//
//

#ifndef __SwampAttack__CrumpEnemySprite__
#define __SwampAttack__CrumpEnemySprite__

#include "EnemySprite.h"

class CrumpEnemySprite : public EnemySprite {
private:
    
protected:
    void    move();
    void    attack();
    void    die();
    void    hurt();
    void    setArmorView();
public:
    void        update(float data);
    CrumpEnemySprite(Enemy * model);
};


#endif /* defined(__SwampAttack__CrumpEnemySprite__) */
