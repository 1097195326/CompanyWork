//
//  House.cpp
//  SwampAttack
//
//  Created by oceantech02 on 15/4/13.
//
//

#include "House.h"
#include "HouseSprite.h"
#include "GameMapManager.h"
#include "GameUser.h"


House::House(): m_health(500.0),
m_baseHealth(m_health),
m_totalHelath(m_health)
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
void House::setView()
{
    HouseSprite * sprite = new HouseSprite();
    sprite->autorelease();
    sprite->setModel(this);
}
void House::hurt(float damage)
{
    m_health -= damage;
    if (m_health <= 0) {
        log("house is over");
        m_state &= _h_clear;
        m_state |= _h_over;
    }
//    log("house health :%f",m_health);
}
void House::addHealth(int health)
{
    m_health = m_totalHelath += health;
//    log("house health :%f",m_health);
//    log("house totalHelath :%f",m_totalHelath);
}
float House::getHealthPercent()
{
    return m_health / m_totalHelath * 100;
}
int House::getStarNum()
{
    float per = getHealthPercent();
    if (per < 0.0001) {
        return 0;
    }else if (per < 50) {
        return 1;
    }else if(per < 99)
    {
        return 2;
    }else
    {
        return 3;
    }
}
bool House::isOver()
{
    return m_state & _h_over;
}
void House::resetData()
{
    m_state &= _h_clear;
    m_health = m_totalHelath = m_baseHealth;
}
void House::reliveGame()
{
    m_state &= _h_clear;
    m_health = m_totalHelath;
}
