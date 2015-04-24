//
//  House.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/13.
//
//

#include "House.h"


House::House(): health(1000)
{
    m_state = _h_clear;
}
House::~House()
{
    
}

House * House::getInstance()
{
    static House house;
    return &house;
}
void House::gameLoop(float data)
{
    
}
void House::hurt(float damage)
{
    health -= damage;
    if (health <= 0) {
        log("house is over");
        m_state &= _h_clear;
        m_state |= _h_over;
    }
    log("house health :%f",health);
}
bool House::isOver()
{
    return m_state & _h_over;
}