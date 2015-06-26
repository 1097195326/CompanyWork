//
//  WalkEnemy.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/23.
//
//

#ifndef __SwampAttack__WalkEnemy__
#define __SwampAttack__WalkEnemy__

#include "Enemy.h"

class WalkEnemy : public Enemy {
private:
    Vec2    m_toPoint;
    Vec2    m_perPoint;
    
    bool    computeIfWander();
protected:
    virtual void    move();
    void    wander();
public:
    
    virtual void    setView();
public:
    WalkEnemy(Json::Value data);
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__WalkEnemy__) */
