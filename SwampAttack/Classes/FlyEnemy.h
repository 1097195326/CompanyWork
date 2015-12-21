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

enum PointState
{
    p_back      = 1 << 0,
    p_front     = 1 << 1,
    p_bottom    = 1 << 2,
    p_up        = 1 << 3,
};

class FlyEnemy : public Enemy {
private:
    int     m_pointState;
    Vec2    m_perPoint;
    Vec2    m_nextPoint;
    Vec2    m_speedVec;
    
    float   dlayToAttack;
    bool    canMoveBack;
private:
    void    setPointState();
    void    randomPoint();
protected:
    virtual void    move();
public:
    void    effectAction(Vec2 point);
    virtual void    setView();
public:
    FlyEnemy(Json::Value data);
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__FlyEnemy__) */
