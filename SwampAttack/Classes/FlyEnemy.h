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
    p_back      = 0b00000001,
    p_front     = 0b00000010,
    p_bottom    = 0b00000100,
    p_up        = 0b00001000,
};

class FlyEnemy : public Enemy {
private:
    int     m_pointState;
    Vec2    m_nextPoint;
    Vec2    m_speedVec;
    
    float   dlayToAttack;
private:
    void    setPointState();
    void    randomPoint();
protected:
    virtual void    move();
public:
    
    virtual void    setView();
public:
    FlyEnemy(Json::Value data);
    void    gameLoop(float data);
};

#endif /* defined(__SwampAttack__FlyEnemy__) */
