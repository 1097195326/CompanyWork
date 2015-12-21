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
    _h_clear    = 0,
    _h_over     = 1,
//    _h_
    
};
class House : public GameObject {
private:
    float   m_health;
    float   m_baseHealth;
    float   m_totalHelath;
    int     m_state;
    
    
private:
    House();
    ~House();
    
public:
    static House * getInstance();
    void    gameLoop(float data);
    void    hurt(float damage);
    void    addHealth(int health);
    void    setView();
    void    resetData();
    void    reliveGame();
public:
    float   getHealthPercent();
    bool    isOver();
    
    
};

#endif /* defined(__SwampAttack__House__) */
