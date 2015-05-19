//
//  House.h
//  SwampAttack
//
//  Created by oceantech02 on 15/4/13.
//
//

#ifndef __SwampAttack__House__
#define __SwampAttack__House__

#include "BaseCode.h"
#include "GameObject.h"


enum HouseState
{
    _h_clear    = 0b00000000,
    _h_over     = 0b00000001,
//    _h_
    
};
class House : public GameObject {
private:
    float   m_health;
    float   m_totalHelath;
    int     m_state;
    
    
private:
    House();
    ~House();
    void    setView();
public:
    static House * getInstance();
    void    gameLoop(float data);
    void    hurt(float damage);
    void    addHealth(int health);
    
public:
    float   getHealthPercent();
    bool    isOver();
    
    
};

#endif /* defined(__SwampAttack__House__) */
