//
//  Enemy.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__Enemy__
#define __SwampAttack__Enemy__

#include "BaseCode.h"
#include "GameObject.h"


class Enemy :public GameObject {
private:
    float m_health;
    Vec2 m_speed;
    Vec2 m_maxSpeed;
    Vec2 m_point;
    Vec2 m_force;
    float m_mass;
    
    
public:
    Enemy();
    ~Enemy();
    
    void gameLoop(float data);
};

#endif /* defined(__SwampAttack__Enemy__) */
